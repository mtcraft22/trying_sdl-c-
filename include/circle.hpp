#include <SDL.h>
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
