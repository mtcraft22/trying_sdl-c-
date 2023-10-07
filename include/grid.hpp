
#include <SDL.h>
#include <iostream>
#include <optional>
#include <string>
#include <map>
#include <vector>
#ifndef grid
#define grid
enum sides {LEFT,RIGHT,TOP,BOTTOM};
enum cell_vertex{TOP_LEFT=1,TOP_RIGHT,BOTTOM_LEFT,BOTTOM_RIGHT};

class terreno{
    public:
        SDL_Vertex poligono1 [3];
        SDL_Vertex poligono2 [3];
        SDL_Point celda [6];
        int indice[3];
        terreno *top;
        terreno *bottom;
        terreno *left;
        terreno *right;
        
        terreno(int tam,SDL_Point init,SDL_Color color);
        
        void set_ayacent(enum sides side, terreno* terreno);
        void move (enum cell_vertex side,int addx,int addy);
        void draw(SDL_Renderer *renderizador,SDL_Texture* tex);

};

#endif