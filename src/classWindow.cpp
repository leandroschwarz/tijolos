// classWindow.cpp

#include "classWindow.hpp"

Window::Window()
{
    this->_posX = 0;
    this->_posY = 0;
    this->_width = 0;
    this->_height = 0;
}

void Window::setPosition(int posX_p, int posY_p)
{
    this->_posX = posX_p;
    this->_posY = posY_p;
}

void Window::setSize(uint16_t width_p, uint16_t height_p)
{
    this->_width = width_p;
    this->_height = height_p;
}

void Window::setBackgroundColor(uint8_t red_p, uint8_t green_p, uint8_t blue_p, uint8_t alpha_p)
{
    this->_backgroundRed = red_p;
    this->_backgroundGreen = green_p;
    this->_backgroundBlue = blue_p;
    this->_backgroundAlpha = alpha_p;
}

SDL_Renderer *Window::getRenderer(void)
{
    return this->_renderer;
}

SDL_Window *Window::getHandler(void)
{
    return this->_handler;
}
