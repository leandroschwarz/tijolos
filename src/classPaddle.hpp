
#ifndef __CLASS_PADDLE_HPP
#define __CLASS_PADDLE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>

class Paddle
{
public:
    Paddle(
            void
    );

    void setPosition(
            int posX_p,
            int posY_p
    );
    int getPosX(
            void
    );
    int getPosY(
            void
    );
    uint16_t getWidth(
            void
    );
    uint16_t getHeight(
            void
    );
    void setVisibility(
            bool visibility_p
    );
    bool getVisibility(
            void
    );
    void setTexture(
            SDL_Texture *texture_p
    );
    SDL_Texture *getTexture(
            void
    );

private:
    int         _posX;
    int         _posY;
    uint16_t    _width;
    uint16_t    _height;
    bool        _visible;
    SDL_Texture *_texture;
};

#endif
