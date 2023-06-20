// classWindow.hpp

#ifndef __CLASS_WINDOW_HPP
#define __CLASS_WINDOW_HPP

#include <cstdint>
#include <SDL2/SDL.h>

class Window
{
public:
    Window();
    void setPosition(
            int posX_p,
            int posY_p
    );
    void setSize(
            uint16_t width_p,
            uint16_t height_p
    );
    void setBackgroundColor(
            uint8_t red_p,
            uint8_t green_p,
            uint8_t blue_p,
            uint8_t alpha_p
    );
    SDL_Renderer *getRenderer(
            void
    );
    SDL_Window *getHandler(
            void
    );

    void create(
            char *title_p
    );

    void cleanUp(
            void
    );

    void fillBackground(
            void
    );
    void presentScene(
            void
    );
    void blit(
            SDL_Texture *texture_p,
            int posX_p,
            int posY_p
    );

private:
    int             _posX;
    int             _posY;
    uint16_t        _width;
    uint16_t        _height;
    uint8_t         _backgroundRed;
    uint8_t         _backgroundGreen;
    uint8_t         _backgroundBlue;
    uint8_t         _backgroundAlpha;
    SDL_Renderer    *_renderer;
    SDL_Window      *_handler;
    char            _title[1024];
};



#endif
