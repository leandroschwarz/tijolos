
// =============================================================================
// Header files
// =============================================================================

#include "defines.hpp"

#include <cstdio>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "classBall.hpp"
#include "classBrick.hpp"
#include "classPaddle.hpp"
#include "classWall.hpp"
#include "classWindow.hpp"
#include "functions.hpp"

Paddle paddle;
Ball ball;
KeyPressed keyPressed;
Window mainWindow;
Wall leftWall;
Wall rightWall;
Wall topWall;

std::vector<Brick> bricks;

int main(int argc, char **argv)
{
    Collision auxCollision;

    // Inicia subsistema de video
    printf("[ INFO ] Iniciando subsistema de vídeo.\n");
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("[ ERRO ] Falha ao inicializar o subsistema de vídeo: %s\n",
                SDL_GetError());
        return 1;
    } else {
        printf("[  OK  ] Subsistema de vídeo iniciado.\n");
    }

    // Configura o escalonador do renderizador
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // Configura a janela principal
    mainWindow.setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    mainWindow.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    mainWindow.setBackgroundColor(64, 128, 255, 255);
    mainWindow.create((char *)"Jogo Tijolos");

    // Define a função de limpeza
    atexit(cleanUp);

    // Carrega as bibliotecas para formatação de imagens
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    // Carrega as texturas para renderização dos objetos
    SDL_Texture *textureSideWall = loadTexture((char *)"imagens/parede.png");
    SDL_Texture *textureTopWall = loadTexture((char *)"imagens/teto.png");
    SDL_Texture *textureBrickRed = loadTexture((char *)"imagens/tijoloVermelho.png");
    SDL_Texture *textureBrickOrange = loadTexture((char *)"imagens/tijoloLaranja.png");
    SDL_Texture *textureBrickYellow = loadTexture((char *)"imagens/tijoloAmarelo.png");
    SDL_Texture *textureBrickGreen = loadTexture((char *)"imagens/tijoloVerde.png");
    SDL_Texture *textureBrickBlue = loadTexture((char *)"imagens/tijoloAzul.png");
    SDL_Texture *textureBrickCyan = loadTexture((char *)"imagens/tijoloCiano.png");
    SDL_Texture *textureBrickPurple = loadTexture((char *)"imagens/tijoloRoxo.png");
    // SDL_Texture *texturePaddle = loadTexture((char *)"imagens/palheta.png");
    SDL_Texture *textureBall = loadTexture((char *)"imagens/bola.png");

    // Configura as paredes
    leftWall.setTexture(textureSideWall);
    leftWall.setPosition(0, 0);
    rightWall.setTexture(textureSideWall);
    rightWall.setPosition(SCREEN_WIDTH - rightWall.getWidth(), 0);
    topWall.setTexture(textureTopWall);
    topWall.setPosition(leftWall.getWidth(), 0);

    // Configura a palheta
    paddle.setTexture(loadTexture((char *)"imagens/palheta.png"));
    paddle.setPosition(((1280 - paddle.getWidth()) / 2), 850);

    // Configura a bola
    ball.setTexture(textureBall);
    ball.setPosition(640.0, 530.0);
    ball.setAngle(30.0);
    ball.setSpeed(6.0);

    // Configurar os tijolos
    Brick auxBrick;
    // Linha de tijolos roxos
    auxBrick.setTexture(textureBrickPurple);
    for(uint8_t i = 0; i < 20; i++) {
        auxBrick.setPosition(40 + i * 60, 100);
        bricks.push_back(auxBrick);
    }
    // Linha de tijolos cianos
    auxBrick.setTexture(textureBrickCyan);
    for(uint8_t i = 0; i < 20; i++) {
        auxBrick.setPosition(40 + i * 60, 140);
        bricks.push_back(auxBrick);
    }
    // Linha de tijolos azuis
    auxBrick.setTexture(textureBrickBlue);
    for(uint8_t i = 0; i < 20; i++) {
        auxBrick.setPosition(40 + i * 60, 180);
        bricks.push_back(auxBrick);
    }
    // Linha de tijolos verdes
    auxBrick.setTexture(textureBrickGreen);
    for(uint8_t i = 0; i < 20; i++) {
        auxBrick.setPosition(40 + i * 60, 220);
        bricks.push_back(auxBrick);
    }
    // Linha de tijolos amarelos
    auxBrick.setTexture(textureBrickYellow);
    for(uint8_t i = 0; i < 20; i++) {
        auxBrick.setPosition(40 + i * 60, 260);
        bricks.push_back(auxBrick);
    }
    // Linha de tijolos laranjas
    auxBrick.setTexture(textureBrickOrange);
    for(uint8_t i = 0; i < 20; i++) {
        auxBrick.setPosition(40 + i * 60, 300);
        bricks.push_back(auxBrick);
    }
    // Linha de tijolos vermelhos
    auxBrick.setTexture(textureBrickRed);
    for(uint8_t i = 0; i < 20; i++) {
        auxBrick.setPosition(40 + i * 60, 340);
        bricks.push_back(auxBrick);
    }

    while(1) {
        eventManager();
        // Move paddle
        auxCollision = checkCollisionAll();
        switch(auxCollision) {
        case Collision::LEFT:
        case Collision::RIGHT:
            ball.setAngle(-ball.getAngle());
            break;
        case Collision::BOTTOM:
        case Collision::TOP:
            ball.setAngle(180 - ball.getAngle());
            break;
        default:
            break;
        }
        movePaddle();
        if(ball.getPosY() < 890) {
            moveBall();
        } else {
            printf("FIM DE JOGO\n");
            exit(0);
        }

        // Preenche fundo da tela
        mainWindow.fillBackground();
        // Desenha as paredes e o teto
        mainWindow.blit(leftWall.getTexture(), leftWall.getPosX(), leftWall.getPosY());
        mainWindow.blit(rightWall.getTexture(), rightWall.getPosX(), rightWall.getPosY());
        mainWindow.blit(topWall.getTexture(), topWall.getPosX(), topWall.getPosY());
        // Desenha a palheta
        mainWindow.blit(paddle.getTexture(), paddle.getPosX(), paddle.getPosY());
        // Desenha a palheta
        mainWindow.blit(ball.getTexture(), ball.getPosX(), ball.getPosY());

        for(Brick &auxBrick : bricks) {
            if(auxBrick.getVisibility()) {
                mainWindow.blit(auxBrick.getTexture(), auxBrick.getPosX(), auxBrick.getPosY());
            }
        }

        mainWindow.presentScene();
        SDL_Delay(16);
    }

    return 0;
}
