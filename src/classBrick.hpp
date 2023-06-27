// classBrick.hpp

#ifndef __CLASS_BRICK_HPP
#define __CLASS_BRICK_HPP

#include <cstdint>
#include <SDL2/SDL_image.h>

class Brick
{
public:
    Brick();
    void setPosition(
            int posX_p,
            int posY_p
    );
    void setSize(
            uint16_t width_p,
            uint16_t height_p
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

    int getPosX(void);
    int getPosY(void);
    uint16_t getWidth(void);
    uint16_t getHeight(void);
    SDL_Texture *getTexture(void);


private:
    int         _posX;
    int         _posY;
    uint16_t    _width;
    uint16_t    _height;
    bool        _visible;
    SDL_Texture *_texture;
};

#endif
