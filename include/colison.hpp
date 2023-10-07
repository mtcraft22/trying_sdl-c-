#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

template<typename T> 
class Colison{
    public:
        Colison(string tag, T shape){
            this->tag=tag;
            this->shape=shape;
        };
        string get_tag();
        T shape;
        void oncolision(Colison colisioned,void(*colision_callback)(void));
        void oncolisionfromtag(string tag,void(*colision_callback)(void));
        void draw(SDL_Renderer* rendeizer);
    private:
        string tag;      
};
