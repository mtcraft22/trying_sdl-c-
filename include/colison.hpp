#pragma once
#include <string>
#include <SDL.h>
#include <circle.hpp>

using namespace std;
class Colison{
    public:
        Colison(string tag);
        string get_tag();
        bool oncolision(SDL_Rect *box);
        bool oncolision(Circle *box);
        void debug_colision(SDL_Renderer* rendeizer);
    protected:
        string tag;      
};
class Rect_colison:public Colison{
    public:
        Rect_colison(string tag, SDL_Rect* box);
        bool oncolision(string tag);
        
    private:
        SDL_Rect * box;
};
class Circle_colison:public Colison{
    public:
        Circle_colison(string tag, Circle* box);
        
        bool oncolision(string tag);
        void debug(SDL_Renderer * renderer);
    private:
        Circle * box;
};
int hash_colision(string colision_tag);
void insert_Circle_colision(int hash, Circle_colison colision);