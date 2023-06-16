// classBrick.cpp


#include "classBrick.hpp"

Brick::Brick()
{
    this->_posX = 0;
    this->_posY = 0;
    this->_width = 0;
    this->_height = 0;
}

void Brick::setPosition(int posX_p, int posY_p)
{
    this->_posX = posX_p;
    this->_posY = posY_p;
}

void Brick::setSize(uint16_t width_p, uint16_t height_p)
{
    this->_width = width_p;
    this->_height = height_p;
}

void Brick::setVisibility(bool visibility_p)
{
    this->_visible = visibility_p;
}

bool Brick::getVisibility(void)
{
    return this->_visible;
}

void Brick::setTexture(SDL_Texture *texture_p)
{
    this->_texture = texture_p;
}
