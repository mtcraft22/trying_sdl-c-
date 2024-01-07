#include <SDL.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <circle.hpp>



Circle::Circle(int x,int y,int r){
   this->x=x;
   this->y=y;
   this->r=r;
}
void Circle::DrawCircle(SDL_Renderer *renderer)
{
   const int diameter = (this->r * 2);

   int x = (this->r - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (y <= x) //the loop goes from center x center y-radius from centerx + radius y
   {
      
      SDL_RenderDrawPoint(renderer, this->x + x, this->y - y);
      SDL_RenderDrawPoint(renderer, this->x + x, this->y + y);
      SDL_RenderDrawPoint(renderer, this->x - x, this->y - y);
      SDL_RenderDrawPoint(renderer, this->x - x, this->y + y);

      SDL_RenderDrawPoint(renderer, this->x + y, this->y - x);
      SDL_RenderDrawPoint(renderer, this->x + y, this->y + x);
      SDL_RenderDrawPoint(renderer, this->x - y, this->y - x);
      SDL_RenderDrawPoint(renderer, this->x - y, this->y + x);
     
      

      // if error negative the poin is iside de circle
      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }
      //if error greater than 0 the point is outer the circle
      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}
