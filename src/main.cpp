
// =============================================================================
// Header files
// =============================================================================

#include <cstdio>
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "classWindow.hpp"
#include "classPaddle.hpp"
#include "classBall.hpp"

#define maximumOf(var1, var2)           ((var1 > var2) ? var1 : var2)
#define minimumOf(var1, var2)           ((var1 < var2) ? var1 : var2)
#define truncateBetween(var, min, max)  ((var < min) ? min : ((var > max) ? max : var))

void cleanUp(void);
void eventManager(void);
SDL_Texture *loadTexture(char *fileName_p);
void doKeyDown(SDL_KeyboardEvent *event);
void doKeyUp(SDL_KeyboardEvent *event);
void movePaddle(void);
void moveBall(void);

struct KeyPressed {
    bool            keyLeftArrow;
    bool            keyRightArrow;
};

enum class Collision {
    NONE            = 0,
    LEFT            = 1,
    RIGHT           = 2,
    BOTTOM          = 3,
    TOP             = 4
};

Collision checkCollisionAll(void);
Collision checkCollision(
        int circCenterX_p,
        int circCenterY_p,
        int circRadius_p,
        int rectPosX_p,
        int rectPosY_p,
        int rectWidth_p,
        int rectHeight_p
);

Window  mainWindow;
Paddle paddle;
Ball ball;
KeyPressed keyPressed;

int main(int argc, char **argv)
{
    Collision auxCollision;

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

    // Carrega as texturas para renderização dos objetos
    SDL_Texture *textureWall = loadTexture((char *)"imagens/parede.png");
    SDL_Texture *textureRoof = loadTexture((char *)"imagens/teto.png");
    // SDL_Texture *textureBrickRed = loadTexture((char *)"imagens/tijoloVermelho.png");
    // SDL_Texture *textureBrickOrange = loadTexture((char *)"imagens/tijoloLaranja.png");
    // SDL_Texture *textureBrickYellow = loadTexture((char *)"imagens/tijoloAmarelo.png");
    // SDL_Texture *textureBrickGreen = loadTexture((char *)"imagens/tijoloVerde.png");
    // SDL_Texture *textureBrickBlue = loadTexture((char *)"imagens/tijoloAzul.png");
    // SDL_Texture *textureBrickCyan = loadTexture((char *)"imagens/tijoloCiano.png");
    // SDL_Texture *textureBrickPurple = loadTexture((char *)"imagens/tijoloRoxo.png");
    SDL_Texture *texturePaddle = loadTexture((char *)"imagens/palheta.png");
    SDL_Texture *textureBall = loadTexture((char *)"imagens/bola.png");

    // Configura a palheta
    paddle.setTexture(texturePaddle);
    paddle.setPosition(((1280 - paddle.getWidth()) / 2), 850);

    // Configura a bola
    ball.setTexture(textureBall);
    ball.setPosition(640.0, 330.0);
    ball.setAngle(30.0);
    ball.setSpeed(3.0);

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
        mainWindow.blit(textureWall, 0, 0);
        mainWindow.blit(textureWall, 1240, 0);
        mainWindow.blit(textureRoof, 40, 0);
        // Desenha a palheta
        mainWindow.blit(paddle.getTexture(), paddle.getPosX(), paddle.getPosY());
        // Desenha a palheta
        mainWindow.blit(ball.getTexture(), ball.getPosX(), ball.getPosY());

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

        case SDL_KEYDOWN:
            doKeyDown(&event.key);
            break;

        case SDL_KEYUP:
            doKeyUp(&event.key);
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

void doKeyDown(SDL_KeyboardEvent *event)
{
    if(event->repeat == 0) {
        if(event->keysym.scancode == SDL_SCANCODE_LEFT) {
            keyPressed.keyLeftArrow = true;
        }

        if(event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            keyPressed.keyRightArrow = true;
        }
    }
}

void doKeyUp(SDL_KeyboardEvent *event)
{
    if(event->repeat == 0) {
        if(event->keysym.scancode == SDL_SCANCODE_LEFT) {
            keyPressed.keyLeftArrow = false;
        }

        if(event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            keyPressed.keyRightArrow = false;
        }
    }
}

void movePaddle(void)
{
    const int paddleSpeed = 10;

    int auxPosX = paddle.getPosX();
    if(keyPressed.keyLeftArrow) {   // Move left
        auxPosX = truncateBetween(auxPosX - paddleSpeed, 40, 1280 - 40 - paddle.getWidth());
    }
    if(keyPressed.keyRightArrow) {  // Move right
        auxPosX = truncateBetween(auxPosX + paddleSpeed, 40, 1280 - 40 - paddle.getWidth());
    }
    paddle.setPosition(auxPosX, paddle.getPosY());
}

void moveBall(void)
{
    float auxPosX = ball.getPosX();
    float auxPosY = ball.getPosY();
    float auxSpeed = ball.getSpeed();
    float auxAngle = ball.getAngle();

    auxPosX += auxSpeed * sin(M_PI * auxAngle / 180.0);
    auxPosY += auxSpeed * cos(M_PI * auxAngle / 180.0);

    ball.setPosition(auxPosX, auxPosY);

}

Collision checkCollisionAll(void)
{
    Collision auxCollision = Collision::NONE;

    // Ball and paddle
    auxCollision = checkCollision(
                    ball.getPosX(),
                    ball.getPosY(),
                    ball.getRadius(),
                    paddle.getPosX(),
                    paddle.getPosY(),
                    paddle.getWidth(),
                    paddle.getHeight()
            );
    if(auxCollision != Collision::NONE) {
        return auxCollision;
    }
    // Ball and left wall
    auxCollision = checkCollision(
                    ball.getPosX(),
                    ball.getPosY(),
                    ball.getRadius(),
                    0,
                    0,
                    40,
                    900
            );
    if(auxCollision != Collision::NONE) {
        return auxCollision;
    }
    // Ball and right wall
    auxCollision = checkCollision(
                    ball.getPosX(),
                    ball.getPosY(),
                    ball.getRadius(),
                    1280 - 40,
                    0,
                    40,
                    900
            );
    if(auxCollision != Collision::NONE) {
        return auxCollision;
    }
    // Ball and roof
    auxCollision = checkCollision(
                    ball.getPosX(),
                    ball.getPosY(),
                    ball.getRadius(),
                    40,
                    0,
                    1200,
                    40
            );
    if(auxCollision != Collision::NONE) {
        return auxCollision;
    }
    // Ball and bricks

    return auxCollision;
}

Collision checkCollision(int circCenterX_p, int circCenterY_p, int circRadius_p, int rectPosX_p, int rectPosY_p,
        int rectWidth_p, int rectHeight_p)
{
    Collision auxDirection = Collision::NONE;

    // Calculate the closest position to the circle in relation to the rectangle
    int closestX = std::max(rectPosX_p, std::min(circCenterX_p, rectPosX_p + rectWidth_p));
    int closestY = std::max(rectPosY_p, std::min(circCenterY_p, rectPosY_p + rectHeight_p));

    // Calculate the closest position to the center of the circle
    int distanciaX = closestX - circCenterX_p;
    int distanciaY = closestY - circCenterY_p;

    // Checks if collision happened
    bool auxCollision = (distanciaX * distanciaX + distanciaY * distanciaY) <= (circRadius_p * circRadius_p);

    if(auxCollision) {
        // Checks side collisions
        if(circCenterX_p < closestX && closestX < circCenterX_p + circRadius_p) {
            auxDirection = Collision::LEFT;
        } else if(circCenterX_p > closestX && closestX > circCenterX_p - circRadius_p) {
            auxDirection = Collision::RIGHT;
        }

        // Checks top and bottom collisions
        if(circCenterY_p < closestY && closestY < circCenterY_p + circRadius_p) {
            auxDirection = Collision::TOP;
        } else if(circCenterY_p > closestY && closestY > circCenterY_p - circRadius_p) {
            auxDirection = Collision::BOTTOM;
        }
    }
    return auxDirection;
}
