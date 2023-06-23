
#include "classBall.hpp"

Ball::Ball()
{
    this->_posX     = 0.0;
    this->_posY     = 0.0;
    this->_speed    = 0.0;
    this->_angle    = 0.0;
    this->_width    = 0;
    this->_height   = 0;
    this->_visible  = true;
    this->_texture  = nullptr;
}

void Ball::setPosition(float posX_p, float posY_p)
{
    this->_posX = posX_p;
    this->_posY = posY_p;
}

float Ball::getPosX(void)
{
    return this->_posX;
}

float Ball::getPosY(void)
{
    return this->_posY;
}

uint16_t Ball::getWidth(void)
{
    return this->_width;
}

uint16_t Ball::getHeight(void)
{
    return this->_height;
}

void Ball::setVisibility(bool visibility_p)
{
    this->_visible = visibility_p;
}

bool Ball::getVisibility(void)
{
    return this->_visible;
}

void Ball::setTexture(SDL_Texture *texture_p)
{
    int auxW, auxH;

    SDL_QueryTexture(texture_p, NULL, NULL, &auxW, &auxH);

    this->_texture = texture_p;
    this->_width = auxW;
    this->_height = auxH;
    this->_radius = auxW / 2;
}

SDL_Texture *Ball::getTexture(void)
{

    return this->_texture;
}

void Ball::setSpeed(float speed_p)
{
    this->_speed = speed_p;
}

void Ball::setAngle(float angle_p)
{
    this->_angle = angle_p;
}

float Ball::getSpeed(void)
{
    return this->_speed;
}

float Ball::getAngle(void)
{
    return this->_angle;
}

float Ball::getRadius(void)
{
    return this->_radius;
}
