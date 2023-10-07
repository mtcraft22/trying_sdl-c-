#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#ifndef circle
#define circle
class Circle{
    public:
        Circle(int x, int y, int r);
        void DrawCircle(SDL_Renderer* renderer);
    private:
        int x,y,r;  
};
#endif 
