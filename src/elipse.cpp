#include <elipse.hpp>

Elipse::Elipse (int x,int y,int r,int r2) : Circle(x,y,r){
    this->r2 = r2;
}
void Elipse::DrawCircle(SDL_Renderer * renderer){
    SDL_Point prev = {0,0};
    prev.x = cos(0)*Circle::getradious()+Circle::getcenterx();
    prev.y = sin(0)*this->r2+Circle::getcentery();

    for (int i = 1 ; i<= 360; i++){

        SDL_RenderDrawLine(renderer, prev.x, prev.y, cos(((float)i/180)*3.1416)*Circle::getradious()+Circle::getcenterx(),sin(((float)i/180)*3.1416)*this->r2+Circle::getcentery());

        prev.x = cos(((float)i/180)*3.1416)*Circle::getradious()+Circle::getcenterx();
        prev.y = sin(((float)i/180)*3.1416)*this->r2+Circle::getcentery();
    }
}