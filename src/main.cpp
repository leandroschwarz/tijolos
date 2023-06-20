
// =============================================================================
// Header files
// =============================================================================

#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "classWindow.hpp"

void cleanUp(void);
void eventManager(void);
SDL_Texture *loadTexture(char *fileName_p);


Window  mainWindow;

int main(int argc, char **argv)
{
    // Inicia subsistema de video
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("[ ERRO ] Falha ao inicializar o subsistema de vídeo: %s\n",
                SDL_GetError());
        return 1;
    } else {
        printf("[ INFO ] Subsistema de vídeo iniciado.\n");
    }

    // Configura o escalonador do renderizador
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // Configura a janela principal
    mainWindow.setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    mainWindow.setSize(1280, 900);
    mainWindow.setBackgroundColor(64, 128, 255, 255);
    mainWindow.create((char *)"Jogo Tijolos");

    // Define a função de limpeza
    atexit(cleanUp);

    // Carrega as bibliotecas para formatação de imagens
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_Texture *textureWall = loadTexture((char *)"imagens/parede.png");
    SDL_Texture *textureRoof = loadTexture((char *)"imagens/teto.png");
    // SDL_Texture *textureBrickRed = loadTexture((char *)"imagens/tijoloVermelho.png");
    // SDL_Texture *textureBrickOrange = loadTexture((char *)"imagens/tijoloLaranja.png");
    // SDL_Texture *textureBrickYellow = loadTexture((char *)"imagens/tijoloAmarelo.png");
    // SDL_Texture *textureBrickGreen = loadTexture((char *)"imagens/tijoloVerde.png");
    SDL_Texture *textureBrickBlue = loadTexture((char *)"imagens/tijoloAzul.png");
    SDL_Texture *textureBrickCyan = loadTexture((char *)"imagens/tijoloCiano.png");
    SDL_Texture *textureBrickPurple = loadTexture((char *)"imagens/tijoloRoxo.png");

    int auxPos = 40;
    bool auxLeft = false;

    while(1) {
        mainWindow.fillBackground();
        mainWindow.blit(textureBrickBlue, auxPos, 240);
        if(auxLeft) {
            auxPos -= 20;
            if(auxPos < 40) {
                auxPos = 40;
                auxLeft = false;
            }
        } else {
            auxPos += 10;
            if(auxPos > 1179) {
                auxPos = 1179;
                auxLeft = true;
            }
        }
        mainWindow.blit(textureWall, 0, 0);
        mainWindow.blit(textureWall, 1240, 0);
        mainWindow.blit(textureRoof, 40, 0);
        for(uint8_t i = 0; i < 20; i++) {
            mainWindow.blit(textureBrickPurple, 40 + (i * 60), 100);
            mainWindow.blit(textureBrickCyan, 40 + (i * 60), 140);
        }

        // mainWindow.blit(test, 90, 200);
        eventManager();
        mainWindow.presentScene();
        SDL_Delay(16);
    }




    return 0;
}

void cleanUp(void)
{
    printf("[ INFO ] Limpando dados.\n");
    mainWindow.cleanUp();
}


void eventManager(void)
{
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
            exit(0);
            break;

        default:
            break;
        }
    }
}

SDL_Texture *loadTexture(char *fileName_p)
{
    SDL_Texture *texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[ INFO ] Carregando arquivo %s", fileName_p);
    texture = IMG_LoadTexture(mainWindow.getRenderer(), fileName_p);

    return texture;
}
