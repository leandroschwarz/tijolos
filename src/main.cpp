
// =============================================================================
// Header files
// =============================================================================

#include <cstdio>
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("[ ERRO ] Falha ao inicializar o subsistema de vídeo: %s\n",
                SDL_GetError());
        return 1;
    } else {
        printf("[ INFO ] Subsistema de vídeo iniciado.\n");
    }

    return 0;
}
