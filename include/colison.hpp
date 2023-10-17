#pragma once

#include "SDL_rect.h"
#include "SDL_render.h"
#include <iostream>
#include <string>

#include <SDL.h>

#include <circle.hpp>

using namespace std;

class Colison{
    public:
        Colison(string tag){
            this->tag=tag;
        };
        string get_tag(){
            return this->tag;
        };
        bool oncolision(SDL_Rect *box);
        bool oncolision(Circle *box);
        void debug_colision(SDL_Renderer* rendeizer);
    protected:
        string tag;      
};
class Rect_colison:Colison{
    public:
        Rect_colison(string tag, SDL_Rect* box):Colison(tag){
            this->box=box;
        }
        bool oncolision(SDL_Rect *box2detec){
            return false;
        }
        bool oncolision(Circle *box2detec){
            return false;
        }
    private:
        SDL_Rect * box;
};
class Circle_colison:Colison{
    public:
        Circle_colison(string tag, Circle* box):Colison(tag){
            this->box=box;
        }
        bool oncolision(SDL_Rect *box2detec){
            return false;
        }
        bool oncolision(Circle *box2detec){
            return sqrt(pow(box2detec->getcenterx()-this->box->getcenterx(),2)+pow(box2detec->getcentery()-this->box->getcentery(),2))<=(box2detec->getradious()+this->box->getradious());
        }
        void debug(SDL_Renderer * renderer){
            this->box->DrawCircle(renderer);
        }
    private:
        Circle * box;
};