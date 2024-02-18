
#include "SDL_video.h"
#include <SDL.h>
#include <iostream>
#include <setup.hpp>

#define WITH 800
#define HEIGHT 600

using namespace std;

bool init_sdl(){
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout<<"SDL could not initialize! SDL_Error: %s\n"<<SDL_GetError();
        return false;
    }else {
        return true;
    }
}
SDL_Window * make_window_(){
    SDL_Window * window = SDL_CreateWindow(
        "Aprendo sdl", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        WITH,
        HEIGHT, 
        SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE| SDL_WINDOW_VULKAN
    );
    if( window == NULL )
    {
        cout << "Window could not be created! SDL_Error: %s\n" << SDL_GetError();
        return NULL;
    }
    else{
        return window;
    }

}