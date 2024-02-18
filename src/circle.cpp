#include "SDL_rect.h"
#include "SDL_render.h"
#include <SDL.h>
#include <circle.hpp>
#include <cmath>
#include <iostream>


Circle::Circle(int x,int y,int r){
   this->x=x;
   this->y=y;
   this->r=r;
  
   srand(time_t(NULL));
}

void Circle::DrawCircle(SDL_Renderer *renderer)
{

    SDL_Point prev = {0,0};
    
    prev.x = cos(0)*this->r+this->x;
    prev.y = sin(0)*this->r+this->y;
    for (int i = 1 ; i<= 360; i++){
      
        SDL_RenderDrawLine(renderer, prev.x, prev.y, cos(((float)i/180)*3.1416)*this->r+this->x,sin(((float)i/180)*3.1416)*this->r+this->y);

        prev.x = cos(((float)i/180)*3.1416)*this->r+this->x;
        prev.y = sin(((float)i/180)*3.1416)*this->r+this->y;
    }
}



