// classWindow.cpp

#include "classWindow.hpp"
#include <cstring>

Window::Window()
{
    this->_posX = 0;
    this->_posY = 0;
    this->_width = 0;
    this->_height = 0;
    this->_backgroundRed = 0;
    this->_backgroundGreen = 0;
    this->_backgroundBlue = 0;
    this->_backgroundAlpha = 0;
    this->_renderer = nullptr;
    this->_handler  = nullptr;
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

void Window::create(char *title_p)
{
    strcpy(this->_title, title_p);
    this->_handler = SDL_CreateWindow(
                    this->_title,
                    this->_posX,
                    this->_posY,
                    this->_width,
                    this->_height,
                    0);
    if(!this->_handler) {
        printf("[ ERRO ] Falha ao criar uma janela de %d x %d: %s\n", this->_width, this->_height, SDL_GetError());
        exit(1);
    } else {
        printf("[ INFO ] Janela '%s' criada.\n", this->_title);
    }

    // Cria o renderizador
    this->_renderer = SDL_CreateRenderer(
                    this->_handler,
                    -1,
                    SDL_RENDERER_ACCELERATED
            );
    if(!this->_renderer) {
        printf("[ ERRO ] Falha ao criar o renderizador: %s\n", SDL_GetError());
        exit(1);
    } else {
        printf("[ INFO ] Renderizador da janela '%s' criado.\n", this->_title);
    }
}

void Window::cleanUp(void)
{
    SDL_DestroyRenderer(this->_renderer);
    SDL_DestroyWindow(this->_handler);
    printf("[ INFO ] Janela '%s' destruída.\n", this->_title);
}

void Window::fillBackground(void)
{
    // Redraw background
    SDL_SetRenderDrawColor(
            this->_renderer,
            this->_backgroundRed,
            this->_backgroundGreen,
            this->_backgroundBlue,
            this->_backgroundAlpha);
    SDL_RenderClear(this->_renderer);
}

void Window::presentScene(void)
{
    SDL_RenderPresent(this->_renderer);
}

void Window::blit(SDL_Texture *texture_p, int posX_p, int posY_p)
{
    SDL_Rect dest;

    dest.x = posX_p;
    dest.y = posY_p;
    SDL_QueryTexture(texture_p, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(this->_renderer, texture_p, NULL, &dest);
}
