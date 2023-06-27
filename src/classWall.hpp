
#ifndef __CLASS_WALL_HPP
#define __CLASS_WALL_HPP

#include <cstdint>
#include <SDL2/SDL.h>

class Wall
{
public:
    Wall(
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

    void setTexture(
            SDL_Texture *texture_p
    );

    SDL_Texture *getTexture(
            void
    );

private:
    float           _posX;
    float           _posY;
    uint16_t        _width;
    uint16_t        _height;
    SDL_Texture     *_texture;
};


#endif
