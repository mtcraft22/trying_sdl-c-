#pragma once
#include <circle.hpp>

class Elipse : public Circle{
    public:
        Elipse (int x,int y,int r,int r2);
        void  DrawCircle(SDL_Renderer * renderer);
    private:
        int r2 ;
};