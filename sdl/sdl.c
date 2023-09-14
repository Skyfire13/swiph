#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0,
            &window,
            &renderer
        );

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    
    while (1) {
        
        SDL_RenderClear(renderer);
        
        // int rand_x = rand() % WINDOW_WIDTH;
        // int rand_y = rand() % WINDOW_HEIGHT;

        int R = rand() % 255;
        int G = rand() % 255;
        int B = rand() % 255;

        SDL_SetRenderDrawColor(renderer, R, G, B, 255);

        for(int i = 0; i < WINDOW_WIDTH; i++) {
            for(int j = 0; j < WINDOW_HEIGHT; j++) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }

        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
