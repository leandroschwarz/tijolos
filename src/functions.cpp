
#include "functions.hpp"
#include "classBall.hpp"
#include "classPaddle.hpp"
#include "classWindow.hpp"
#include <iostream>
#include <cstdint>
#include <cmath>

extern Paddle paddle;
extern Ball ball;
extern Window mainWindow;
extern KeyPressed keyPressed;

Collision checkCollision(int cPosX_p, int cPosY_p, int cRadius_p, int rPosX_p, int rPosY_p, int rWidth_p, int rHeight_p)
{
    Collision auxCollision = Collision::NONE;
    int circCenterX = cPosX_p + cRadius_p;
    int circCenterY = cPosY_p + cRadius_p;

    // Calculate the closest position to the circle in relation to the rectangle
    int closestX = std::max(rPosX_p, std::min(circCenterX, rPosX_p + rWidth_p));
    int closestY = std::max(rPosY_p, std::min(circCenterY, rPosY_p + rHeight_p));

    // Calculate the closest position to the center of the circle
    int deltaX = closestX - circCenterX;
    int deltaY = closestY - circCenterY;

    // Checks if collision happened
    if((deltaX * deltaX + deltaY * deltaY) <= (cRadius_p * cRadius_p)) {
        // Checks side collisions
        if(circCenterX < closestX && closestX < circCenterX + cRadius_p) {
            auxCollision = Collision::LEFT;
        } else if(circCenterX > closestX && closestX > circCenterX - cRadius_p) {
            auxCollision = Collision::RIGHT;
        }

        // Checks top and bottom collisions
        if(circCenterY < closestY && closestY < circCenterY + cRadius_p) {
            auxCollision = Collision::TOP;
        } else if(circCenterY > closestY && closestY > circCenterY - cRadius_p) {
            auxCollision = Collision::BOTTOM;
        }
    }
    return auxCollision;
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

void cleanUp(void)
{
    printf("[ INFO ] Limpando dados.\n");
    mainWindow.cleanUp();
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
    SDL_Texture *auxTexture;
    printf("[ INFO ] Carregando arquivo %s\n", fileName_p);
    auxTexture = IMG_LoadTexture(mainWindow.getRenderer(), fileName_p);
    if(!auxTexture) {
        printf("[ ERRO ] Erro ao carregar o arquivo %s: %s\n", fileName_p, SDL_GetError());
    } else {
        printf("[  OK  ] Arquivo %s carregado com sucesso!\n", fileName_p);
    }

    return auxTexture;
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
