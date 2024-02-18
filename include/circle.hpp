#include <SDL.h>
#pragma once
class Circle{
    public:
        Circle(int x, int y, int r);
        void DrawCircle(SDL_Renderer* renderer);
        int getcenterx(){
            return this->x;
        }
        int getcentery(){
            return this->y;
        }
        int getradious(){
            return this->r;
        }
        void setx(int x){
            this->x=x;
        }
        void sety(int y){
            this->y=y;
        }
        void setradious(int r){
            if (r>0){
                this->r=r;
            }
        }
    private:
     
    
        int x,y,r;  
};
