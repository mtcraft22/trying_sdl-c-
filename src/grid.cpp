#include "SDL_events.h"
#include <SDL.h> 
#include <iostream>
#include <grid.hpp>
#include <string>

using namespace std;
//constructor de terreno


terreno::terreno(int tam,SDL_Point init,SDL_Color color){
    
    this->top=NULL;
    this->bottom=NULL;
    this->left=NULL;
    this->right=NULL;
    this->tam= tam;

    this->celda[0]={init.x,init.y};
    this->celda[1]={init.x+this->tam,init.y};
    this->celda[2]={init.x-(this->tam/2)+this->tam,init.y+(this->tam/2)};

    this->celda[3]={init.x-(this->tam/2),init.y+(this->tam/2)};
    this->celda[4]={init.x,init.y};
    this->celda[5]={init.x-(this->tam/2)+this->tam,init.y+(this->tam/2)};
    
    this->indice[0]=0;
    this->indice[1]=1;
    this->indice[2]=2;


    this->poligono1[0]={(float)init.x,(float)init.y,color,0.0f,0.0f};
    this->poligono1[1]={(float)init.x+tam,(float)init.y,color,1.0f,0.0f};
    this->poligono1[2]={(float)init.x-((float)tam/2)+tam,(float)init.y+((float)tam/2),color,1.0f,1.0f};
    this->poligono2[0]={(float)init.x-(float)tam/2,(float)init.y+(float)tam/2,color,0.0f,1.0f};
    this->poligono2[1]={(float)init.x,(float)init.y,color,0.0f,0.0f};
    this->poligono2[2]={(float)init.x-(float)tam/2+tam,(float)init.y+(float)tam/2,color,1.0f,1.0f};
}

/*
    funcion para definir las celdas ayacentes para asi quando 
    se mueva la esquina de una celda se mueva tambien la esquina 
    corrresponiente a la celda de a lado.
    Param side puede ser : 
    l:(celda de la izquierda),
    r:(celda de la derecha),
    t:(celda de ariba),
    b:(celda de abajo),
*/
void terreno::set_ayacent(enum sides side, terreno *celda){
    switch (side) {
        case TOP:
            this->top=celda;
            break;
        case BOTTOM:
            this->bottom=celda;
            break;
        case LEFT:
            this->left=celda;
            break;
        case RIGHT:
            this->right=celda;
            break;
    }
}
/*
    throw a ilegal argument when the side argument is wrong
*/
/***
    @brief move a vertex of a grid tile
*/
void terreno::move(enum cell_vertex side, float addx,float addy){
    
    switch (side) {
        case TOP_LEFT:
            this->celda[0].x+=addx;
            this->celda[0].y+=addy;
            this->celda[4].x+=addx;
            this->celda[4].y+=addy;
            this->poligono1[0].position.x=(float)this->celda[0].x;
            this->poligono1[0].position.y=(float)this->celda[0].y;
            this->poligono2[1].position.x=(float)this->celda[4].x;
            this->poligono2[1].position.y=(float)this->celda[4].y;
           
            if (this->top != NULL){
                //this->top->move(BOTTOM_LEFT, addx, addy);
                this->top->celda[3].x += addx;
                this->top->celda[3].y += addy;
                this->top->poligono2[0].position.x = (float)this->top->celda[3].x;
                this->top->poligono2[0].position.y = (float)this->top->celda[3].y;
            }
            if (this->left != NULL){
                this->left->celda[1].x += addx;
                this->left->celda[1].y += addy;
                this->left->poligono1[1].position.x = (float)this->left->celda[1].x;
                this->left->poligono1[1].position.y = (float)this->left->celda[1].y;
            }
            break;

        case TOP_RIGHT:
            this->celda[1].x+=addx;
            this->celda[1].y+=addy;
            this->poligono1[1].position.x=(float)this->celda[1].x;
            this->poligono1[1].position.y=(float)this->celda[1].y;
            if (this->right != NULL){
                //this->right->move(TOP_LEFT,addx, addy);
                this->right->celda[0].x += addx;
                this->right->celda[0].y += addy;
                this->right->celda[4].x += addx;
                this->right->celda[4].y += addy;
                this->right->poligono1[0].position.x = (float)this->right->celda[0].x;
                this->right->poligono1[0].position.y = (float)this->right->celda[0].y;
                this->right->poligono2[1].position.x = (float)this->right->celda[4].x;
                this->right->poligono2[1].position.y = (float)this->right->celda[4].y;
            }
            if (this->top != NULL){
                //this->top->move(BOTTOM_RIGHT,addx, addy);
                this->top->celda[5].y += addy;
                this->top->celda[2].y += addy;
                this->top->celda[5].x += addx;
                this->top->celda[2].x += addx;
                this->top->poligono1[2].position.y = (float)this->top->celda[2].y;
                this->top->poligono2[2].position.y = (float)this->top->celda[5].y;
                this->top->poligono1[2].position.x = (float)this->top->celda[2].x;
                this->top->poligono2[2].position.x = (float)this->top->celda[5].x;
            }
            break;
        case BOTTOM_RIGHT:
            this->celda[5].y+=addy;
            this->celda[2].y+=addy;
            this->celda[5].x+=addx;
            this->celda[2].x+=addx;
            this->poligono1[2].position.y=(float)this->celda[2].y;
            this->poligono2[2].position.y=(float)this->celda[5].y;
            this->poligono1[2].position.x=(float)this->celda[2].x;
            this->poligono2[2].position.x=(float)this->celda[5].x;
            if (this->right != NULL){
                //this->right->move(BOTTOM_LEFT,addx, addy);
                this->right->celda[3].x += addx;
                this->right->celda[3].y += addy;
                this->right->poligono2[0].position.x = (float)this->right->celda[3].x;
                this->right->poligono2[0].position.y = (float)this->right->celda[3].y;
            }
            if (this->bottom != NULL){
                //this->bottom->move(TOP_RIGHT, addx, addy);
                this->bottom->celda[1].x += addx;
                this->bottom->celda[1].y += addy;
                this->bottom->poligono1[1].position.x = (float)this->bottom->celda[1].x;
                this->bottom->poligono1[1].position.y = (float)this->bottom->celda[1].y;
            }
            break;
        case BOTTOM_LEFT:
            this->celda[3].x+=addx;
            this->celda[3].y+=addy;
            this->poligono2[0].position.x=(float)this->celda[3].x;
            this->poligono2[0].position.y=(float)this->celda[3].y;
            
            if (this->left != NULL){
                //this->left->move(BOTTOM_RIGHT,addx, addy);
                this->left->celda[5].y += addy;
                this->left->celda[2].y += addy;
                this->left->celda[5].x += addx;
                this->left->celda[2].x += addx;
                this->left->poligono1[2].position.y = (float)this->left->celda[2].y;
                this->left->poligono2[2].position.y = (float)this->left->celda[5].y;
                this->left->poligono1[2].position.x = (float)this->left->celda[2].x;
                this->left->poligono2[2].position.x = (float)this->left->celda[5].x;
            }
            if (this->bottom != NULL){
                //this->bottom->move(TOP_LEFT, addx, addy);
                this->bottom->celda[0].x += addx;
                this->bottom->celda[0].y += addy;
                this->bottom->celda[4].x += addx;
                this->bottom->celda[4].y += addy;
                this->bottom->poligono1[0].position.x = (float)this->bottom->celda[0].x;
                this->bottom->poligono1[0].position.y = (float)this->bottom->celda[0].y;
                this->bottom->poligono2[1].position.x = (float)this->bottom->celda[4].x;
                this->bottom->poligono2[1].position.y = (float)this->bottom->celda[4].y;

            }
            break;
        default:
            throw invalid_argument("El argumento para side es incorecto");
    }
}
/***
@brief render a tile
*/
void terreno::draw(SDL_Renderer* renderizador,SDL_Texture* tex){
    SDL_RenderGeometry(renderizador, tex, this->poligono1, 3, this->indice, 3);
    SDL_RenderGeometry(renderizador, tex, this->poligono2, 3, this->indice, 3);
    //SDL_RenderDrawLines(renderizador, this->celda, 6);
}
bool terreno::mouse_hit(SDL_Event* e) {
    int yoff  = e->motion.y - this->poligono1[0].position.y ;
    bool iny = e->motion.y > this->poligono1[0].position.y && e->motion.y < (this->poligono1[0].position.y + (int)(this->tam/2));
    bool inx = e->motion.x > (this->poligono1[0].position.x-yoff) && e->motion.x < (this->poligono1[0].position.x - yoff)+this->tam;
    bool in = iny && inx;
    return in ;
}