#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>


/**
 * Instructions found at:
 * https://glusoft.com/sdl2-tutorials/display-image-sdl_image/
 */


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(int argc, char **argv) {

    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_EVENTS < 0)) {
        printf("Error SDL2 Initialization: %s\n", SDL_GetError());
        return 1;
    }

    if(IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Error SDL2_image Initialization\n");
        return 2;
    }

    SDL_Window* window = SDL_CreateWindow(
            "Bellchamp",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL
        );
    if(window == NULL) {
        printf("Error window creation\n");
        return 3;
    }

    /*
     * 1. Window where the rendering will occur
     * 2. Rendering driver, -1 uses the first available option
     * 3. Mode of the renderer
     */
    SDL_Renderer* renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
        );
    if(renderer == NULL) {
        printf("Error renderer creation\n");
        return 4;
    }

    /*
     * A surface is an array of pixels stored in RAM, encoded in 
     * a specific format, usually RGBA
     */
    
    SDL_Surface* bellchamp_sur = IMG_Load("bellchamp.png");
    if(bellchamp_sur == NULL) {
        printf("Error loading image\n");
        return 5;
    }


    /*
     * An SDL_Texture is an array of pixels stored in VRAM
     * encoded in a driver-specific format
     */
    SDL_Texture* bellchamp_tex = SDL_CreateTextureFromSurface(renderer, bellchamp_sur);
    if(bellchamp_tex == NULL) {
        printf("Error creating texture\n");
        return 6;
    }
    SDL_FreeSurface(bellchamp_sur);

    // Event Loop
    while(1) {
        SDL_Event e;
        if(SDL_WaitEvent(&e)) {
            if(e.type == SDL_QUIT) {
                break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bellchamp_tex, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bellchamp_tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

