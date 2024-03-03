#include <SDL.h>
#include <chunck.hpp>
#include <grid.hpp>
#include <vector>




Chunck::Chunck(int celgrid, int nrow, int ncolumns, int ix, int iy, SDL_Color *color) {
  this->ncolumns=ncolumns;
  this->nrow = nrow;
  this->gridSize = celgrid;
  this->root.x = ix;
  this->root.y = iy;
  this->startRoot.x = ix;
  this->startRoot.y = iy;
  Chunck::push_grid(color);
  Chunck::bind_grid();
}
void Chunck::draw_chunk(SDL_Renderer *renderer, SDL_Texture *tex) {
  for (vector<terreno *> i : gridgroup) {
    for (terreno *ter2 : i) {
      ter2->draw(renderer, tex);
    }
  }
}

void Chunck::push_grid(SDL_Color *color) {

  for (int y = 0; y < this->ncolumns; y++) {
    for (int x = 0; x < this->ncolumns; x++) {

      terreno *cel = new terreno(this->gridSize, this->root, *(color));

      this->Grid.push_back(cel);
      this->root.x += this->gridSize;
    }
    this->gridgroup.push_back(this->Grid);
    this->Grid.clear();
    this->root.y += this->gridSize / 2;
    this->root.x = this->startRoot.x - ((this->gridSize / 2) * (y + 1));
  }
}
void Chunck::bind_grid() {
  for (int y = 0; y <= this->gridgroup.size() - 1; y++) {
    for (int x = 0; x <= this->gridgroup.at(y).size() - 1; x++) {
      if (x + 1 <= this->gridgroup.at(y).size() - 1) {
        this->gridgroup[y][x]->set_ayacent(RIGHT, this->gridgroup[y][x + 1]);
      }
      if (y + 1 <= this->gridgroup.size() - 1) {
        this->gridgroup[y][x]->set_ayacent(BOTTOM, this->gridgroup[y + 1][x]);
      }
      if (x - 1 >= 0) {
        this->gridgroup[y][x]->set_ayacent(LEFT, this->gridgroup[y][x - 1]);
      }
      if (y - 1 >= 0) {
        this->gridgroup[y][x]->set_ayacent(TOP, this->gridgroup[y - 1][x]);
      }
    }
  }
}
Chunck::~Chunck() {
  for (vector<terreno *> i : this->gridgroup) {
    for (terreno *ter : i) {
      delete ter;
    }
  }
}