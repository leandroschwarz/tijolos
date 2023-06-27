
#ifndef __FUNCTIONS_HPP
#define __FUNCTIONS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defines.hpp"

Collision checkCollision(
        int cPosX_p,
        int cPosY_p,
        int cRadius_p,
        int rPosX_p,
        int rPosY_p,
        int rWidth_p,
        int rHeight_p
);

Collision checkCollisionAll(
        void
);

void cleanUp(
        void
);

void doKeyDown(
        SDL_KeyboardEvent *event_p
);

void doKeyUp(
        SDL_KeyboardEvent *event_p
);

void eventManager(
        void
);

SDL_Texture *loadTexture(
        char *fileName_p
);

void moveBall(
        void
);

void movePaddle(
        void
);

#endif
