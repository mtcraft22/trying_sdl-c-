#include <SDL2/SDL.h> 
#include <SDL2/SDL_render.h>
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
    this->celda[0]={init.x,init.y};
    this->celda[1]={init.x+tam,init.y};
    this->celda[2]={init.x-(tam/2)+tam,init.y+(tam/2)};

    this->celda[3]={init.x-(tam/2),init.y+(tam/2)};
    this->celda[4]={init.x,init.y};
    this->celda[5]={init.x-(tam/2)+tam,init.y+(tam/2)};
    
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
void terreno::move(enum cell_vertex side, int addx,int addy){
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
           
            if (this->top){
                this->top->move(BOTTOM_LEFT, addx, addy);
            }
            if (this->left){
                this->left->move(TOP_RIGHT, addx, addy);
            }
            break;

        case TOP_RIGHT:
            this->celda[1].x+=addx;
            this->celda[1].y+=addy;
            this->poligono1[1].position.x=(float)this->celda[1].x;
            this->poligono1[1].position.y=(float)this->celda[1].y;
            if (this->right){
                this->right->move(TOP_LEFT,addx, addy);
            }
            if (this->top){
                this->top->move(BOTTOM_RIGHT,addx, addy);
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
            if (this->right){
                this->right->move(BOTTOM_LEFT,addx, addy);
            }
            if (this->bottom){
                this->bottom->move(TOP_RIGHT, addx, addy);
            }
            break;
        case BOTTOM_LEFT:
            this->celda[3].x+=addx;
            this->celda[3].y+=addy;
            this->poligono2[0].position.x=(float)this->celda[3].x;
            this->poligono2[0].position.y=(float)this->celda[3].y;
            
            if (this->left){
                this->left->move(BOTTOM_RIGHT,addx, addy);
            }
            if (this->bottom){
                this->bottom->move(TOP_LEFT, addx, addy);
            }
            break;
        default:
            throw invalid_argument{"Ilegal cell side"};
    }

}
void terreno::draw(SDL_Renderer* renderizador,SDL_Texture* tex){
    SDL_RenderGeometry(renderizador, tex, this->poligono1, 3, this->indice, 3);
    SDL_RenderGeometry(renderizador, tex, this->poligono2, 3, this->indice, 3);
    SDL_RenderDrawLines(renderizador, this->celda, 6);
}