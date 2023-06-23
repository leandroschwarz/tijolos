

#include "classPaddle.hpp"

// classPaddle.cpp

#include "classPaddle.hpp"

Paddle::Paddle()
{
    this->_posX = 0;
    this->_posY = 0;
    this->_width = 0;
    this->_height = 0;
    this->_visible = true;
    this->_texture = nullptr;
}

void Paddle::setPosition(int posX_p, int posY_p)
{
    this->_posX = posX_p;
    this->_posY = posY_p;
}

int Paddle::getPosX(void)
{
    return this->_posX;
}

int Paddle::getPosY(void)
{
    return this->_posY;
}

uint16_t Paddle::getWidth(void)
{
    return this->_width;
}

uint16_t Paddle::getHeight(void)
{
    return this->_height;
}

void Paddle::setVisibility(bool visibility_p)
{
    this->_visible = visibility_p;
}

bool Paddle::getVisibility(void)
{
    return this->_visible;
}

void Paddle::setTexture(SDL_Texture *texture_p)
{
    int auxW, auxH;

    SDL_QueryTexture(texture_p, NULL, NULL, &auxW, &auxH);

    this->_texture = texture_p;
    this->_width = auxW;
    this->_height = auxH;
}

SDL_Texture *Paddle::getTexture(void)
{
    return this->_texture;
}
