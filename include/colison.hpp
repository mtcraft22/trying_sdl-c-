#pragma once
#include <SDL.h>
#include <iostream>
#include <string>

using namespace std;

class Colison{
    public:
        Colison(string tag){
            this->tag=tag;
        };
        string get_tag(){
            return this->tag;
        };
        void oncolision(Colison colisioned,void(*colision_callback)(void));
        void oncolision(string tag,void(*colision_callback)(void));
        void debug_colision(SDL_Renderer* rendeizer);
    protected:
        string tag;      
};
class Rect_colison:Colison{
    public:
        Rect_colison(string tag, SDL_Rect* box):Colison(tag){
            this->box=box;
        }
    private:
        SDL_Rect * box;
        
};