

#include <SDL.h>

#ifndef grid
#define grid
enum sides {LEFT,RIGHT,TOP,BOTTOM};
enum cell_vertex{TOP_LEFT=1,TOP_RIGHT,BOTTOM_LEFT,BOTTOM_RIGHT};

class terreno{
    public:
        SDL_Vertex poligono1 [3];
        SDL_Vertex poligono2 [3];
        SDL_Point celda [6];
        int indice[4];
        int tam;
        terreno *top;
        terreno *bottom;
        terreno *left;
        terreno *right;
        
        terreno(int tam,SDL_Point init,SDL_Color color);
        
        void set_ayacent(enum sides side, terreno* terreno);
        void move (enum cell_vertex side,float addx,float addy);
        void draw(SDL_Renderer *renderizador,SDL_Texture* tex);
        bool point_hit(int x, int y);
};

#endif