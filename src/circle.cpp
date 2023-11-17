#include <SDL.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <circle.hpp>

#include <iostream>
#include <ostream>


Circle::Circle(int x,int y,int r){
   this->x=x;
   this->y=y;
   this->r=r;
}
void Circle::DrawCircle(SDL_Renderer *renderer)
{
   const int32_t diameter = (this->r * 2);

   int32_t x = (this->r - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      
      SDL_RenderDrawPoint(renderer, this->x + x, this->y - y);
      SDL_RenderDrawPoint(renderer, this->x + x, this->y + y);
      SDL_RenderDrawPoint(renderer, this->x - x, this->y - y);
      SDL_RenderDrawPoint(renderer, this->x - x, this->y + y);

      SDL_RenderDrawPoint(renderer, this->x + y, this->y - x);
      SDL_RenderDrawPoint(renderer, this->x + y, this->y + x);
      SDL_RenderDrawPoint(renderer, this->x - y, this->y - x);
      SDL_RenderDrawPoint(renderer, this->x - y, this->y + x);
     



      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}
