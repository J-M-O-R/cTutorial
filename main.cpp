#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

using namespace std;

int main()
{
    const int WINDOW_WIDTH {800};
    const int WINDOW_HEIGHT {600};

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL init failed!!!" << endl;
        return 1;
    }

    SDL_Window* window {SDL_CreateWindow("Particle Fire Explosion",
                                         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                         WINDOW_WIDTH, WINDOW_HEIGHT,
                                         SDL_WINDOW_SHOWN)};
    if(window == nullptr) {
        SDL_Quit();
        return 2;
    }

    SDL_Event event;

    bool quit {false};
    while(!quit) {
        //
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
