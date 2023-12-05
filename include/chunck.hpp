#pragma once

#include <vector>
#include <SDL.h>
#include <grid.hpp>

using namespace std;

class Chunck {
public:
   Chunck(int celgrid, int nrow, int ncolumns, int ix, int iy, SDL_Color *color);

    void draw_chunk(SDL_Renderer *renderer, SDL_Texture* tex);
    ~Chunck();
    vector<terreno *> Grid ;
    vector<vector<terreno *>> gridgroup;
    SDL_Point root = {0,0};
    SDL_Point startRoot = {0,0};
    int gridSize, nrow,ncolumns;
    void push_grid(SDL_Color * color);
    void bind_grid();
};
