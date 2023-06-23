

#ifndef __CLASS_BALL_HPP
#define __CLASS_BALL_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Ball
{
public:
    Ball();
    void setPosition(float posX_p, float posY_p);
    float getPosX(void);
    float getPosY(void);
    float getRadius(void);
    uint16_t getWidth(void);
    uint16_t getHeight(void);
    void setVisibility(bool visibility_p);
    bool getVisibility(void);
    void setTexture(SDL_Texture *texture_p);
    SDL_Texture *getTexture(void);
    void setSpeed(float speed_p);
    void setAngle(float angle_p);
    float getSpeed(void);
    float getAngle(void);

private:
    float           _posX;
    float           _posY;
    float           _speed;
    float           _angle;
    float           _radius;
    bool            _visible;
    uint16_t        _width;
    uint16_t        _height;
    SDL_Texture     *_texture;
};

#endif
