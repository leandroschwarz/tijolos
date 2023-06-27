
#include "classWall.hpp"

Wall::Wall()
{
    this->_posX = 0;
    this->_posY = 0;
    this->_width = 0;
    this->_height = 0;
    this->_texture = nullptr;
}

void Wall::setPosition(int posX_p, int posY_p)
{
    this->_posX = posX_p;
    this->_posY = posY_p;
}

int Wall::getPosX(void)
{
    return this->_posX;
}

int Wall::getPosY(void)
{
    return this->_posY;
}

uint16_t Wall::getWidth(void)
{
    return this->_width;
}

uint16_t Wall::getHeight(void)
{
    return this->_height;
}

void Wall::setTexture(SDL_Texture *texture_p)
{
    int auxW, auxH;

    SDL_QueryTexture(texture_p, NULL, NULL, &auxW, &auxH);

    this->_texture = texture_p;
    this->_width = auxW;
    this->_height = auxH;
}

SDL_Texture *Wall::getTexture(void)
{
    return this->_texture;
}
