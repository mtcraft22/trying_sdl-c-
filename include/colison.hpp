#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>
#include <tuple>

#ifndef colison
#define colison
using namespace std;

template<typename T> 
class Colison{
    public:
        string get_tag();
        T shape;
        void oncolision(Colison colisioned,void(*colision_callback)(void));
        void draw(SDL_Renderer* rendeizer);
    private:
        string tag;
        
};
#endif
