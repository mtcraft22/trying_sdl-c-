#include "SDL_events.h"
#include "SDL_mouse.h"
#include "SDL_pixels.h"
#include <exception>
#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include <ostream>
#include <setup.hpp>
#include <grid.hpp>
#include <circle.hpp>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    if (!init_sdl()) {
        cout << SDL_GetError();
        return -1;
    }
    SDL_Window* window;
    window = make_window_();
    if (!window) {
        cout << "No se inició pantalla" << SDL_GetError();
        return -1;
    }
    SDL_Renderer* renderizador = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* texture_surface = IMG_Load("./resources/bueno.png");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderizador, texture_surface);
    //cargamos al personaje principal

    SDL_Surface* pepe = IMG_Load("./resources/pepe.png");
    SDL_Texture* pepe_text = SDL_CreateTextureFromSurface(renderizador, pepe);
    //cargamos la textura de la segunda capa
    SDL_Surface* segunda_capa = IMG_Load("./resources/ladrillo.png");
    SDL_Texture* capa2_text = SDL_CreateTextureFromSurface(renderizador, segunda_capa);
    if (!tex) { cout << "sdl_texture_load" << SDL_GetError() << std::endl; }

    SDL_Color col{ 0xff,0xff,0xff,0xff};

    SDL_Point root;

    terreno celdas [10][10] = {
        {terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col)},
        {terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col)},
        {terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col)},
        {terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col)},
        {terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col)},
        {terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col)},
        {terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col)},
        {terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col)},
        {terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col)},        
        {terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col),terreno(0,root,col)},        

    };
   
  
    root = {300,100};
  
    for (int y=0;y<9;y++){
        for (int x=0;x<9;x++){
            
            terreno cel = terreno(60,root,col);
            
            celdas[y][x] = cel;
            root.x += 60;
        }
        root.y += 30;
        root.x = 300-(30*(y+1));
    }

    
    for (int y= 0;y<9;y++){
        for (int x = 0;x<9;x++){   
            
            celdas[y][x].set_ayacent(RIGHT, &celdas[y][x+1]);
            celdas[y][x].set_ayacent(BOTTOM, &celdas[y+1][x]);
            if (x>0){
                celdas[y][x].set_ayacent(LEFT, &celdas[y][x-1]);
            }
            
            
        }
    }
    SDL_Event e;
    
    bool quit = false;
    SDL_Vertex pepe_forma[3] = {
        {200,200,col,0.0f,0.0f},
        {250,200,col,1.0f,0.0f},
        {200,250,col,0.0f,1.0f}

    };
    SDL_Vertex pepe_forma2[3] = {
        {200,250,col,0.0f,1.0f},
        {250,250,col,1.0f,1.0f},
        {250,200,col,1.0f,0.0f}

    };
    int indices_pepe[4] = { 0,1,2 };
    SDL_Rect rec = { 20,20,50,50 };
    Circle circulo = Circle(450, 200, 100);
    Circle mouse_box = Circle(450, 0, 25);
    int cx, cy = 0;
    int size = 25;
    int r, g, b, a = 0;
    r = 0;
    g = 255;
    b = 0;
    a = 255;
    unsigned int ycel;
    unsigned int xcel;
    float xcelreal;
    float ycelreal;
    float xcelofft = xcelreal -xcel;
    float ycelofft = ycelreal -ycel;
    terreno *seleciono = &celdas[0][0];
    while (!quit) {
        
        SDL_RenderClear(renderizador);

        SDL_SetRenderDrawColor(renderizador,r,g,b,a);
        SDL_SetRenderDrawBlendMode(renderizador,SDL_BLENDMODE_ADD);
        
        
        
        
        for (int y=0;y<9;y++){
            for (int x=0;x<9;x++){
                celdas[y][x].draw(renderizador, tex);
            }
        }
        if ((ycel>=0 && ycel<=8)&&(xcel>=0 && xcel<=8)){
            celdas[ycel][xcel].poligono1[0].color=col;
            celdas[ycel][xcel].poligono1[1].color=col;
            celdas[ycel][xcel].poligono1[2].color=col;

        }
        
        //SDL_RenderDrawLine(renderizador, rec.x + (rec.w / 2), rec.y + (rec.h / 2), circulo.getcenterx(), circulo.getcentery());
        //SDL_RenderDrawRect(renderizador, &rec);
        //SDL_RenderGeometry(renderizador, pepe_text, pepe_forma, 3, indices_pepe, 3);
        //SDL_RenderGeometry(renderizador, pepe_text, pepe_forma2, 3, indices_pepe, 3);
        //circulo.DrawCircle(renderizador);
        //mouse_box.DrawCircle(renderizador);
        //SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
        SDL_RenderPresent(renderizador);
        SDL_SetRenderDrawColor(renderizador,0,0,0,255);
        xcelofft = xcelreal -xcel;
        ycelofft = ycelreal -ycel;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) { quit = true; }
            else if (e.type==SDL_MOUSEBUTTONDOWN) {
                switch (e.button.button) {
                    case SDL_BUTTON_LEFT:

                        if (xcelofft > 0.5 && ycelofft <=0.5){
                            seleciono->move(TOP_RIGHT, 0, 1);
                            break;
                            
                        }
                        else if (xcelofft <=0.5 && ycelofft <=0.5){
                            seleciono->move(TOP_LEFT, 0, 1);
                            break;
                           
                        }
                        else if (xcelofft > 0.5 && ycelofft >0.5){
                            seleciono->move(BOTTOM_RIGHT, 0, 1);
                            break;
                            
                        }
                        else if (xcelofft <=0.5 && ycelofft >0.5){
                            seleciono->move(BOTTOM_LEFT, 0, 1);
                            break;
                           
                        }
                    
                        break;
                    case SDL_BUTTON_RIGHT:
                        if (xcelofft > 0.5 && ycelofft <=0.5){
                            seleciono->move(TOP_RIGHT, 0, -1);
                            break;
                            
                        }
                        else if (xcelofft <=0.5 && ycelofft <=0.5){
                            seleciono->move(TOP_LEFT, 0, -1);
                            break;
                           
                        }
                        else if (xcelofft > 0.5 && ycelofft >0.5){
                            seleciono->move(BOTTOM_RIGHT, 0, -1);
                            break;
                            
                        }
                        else if (xcelofft <=0.5 && ycelofft >0.5){
                            seleciono->move(BOTTOM_LEFT, 0, -1);
                            break;
                           
                        }
                }
            }
            /*else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_q:
                    celda5.move(TOP_LEFT, 0, -1);
                    break;
                case SDLK_a:
                    celda5.move(TOP_LEFT, 0, 1);
                    break;
                case SDLK_w:
                    celda5.move(TOP_RIGHT, 0, -1);
                    break;
                case SDLK_s:
                    celda5.move(TOP_RIGHT, 0, 1);
                    break;
                case SDLK_e:
                    celda5.move(BOTTOM_LEFT, 0, -1);
                    break;
                case SDLK_d:
                    celda5.move(BOTTOM_LEFT, 0, 1);
                    break;
                case SDLK_r:
                    celda5.move(BOTTOM_RIGHT, 0, -1);
                    break;
                case SDLK_f:
                    celda5.move(BOTTOM_RIGHT, 0, 1);
                    break;

                }
            }*/
            
            ycel=(int)(e.motion.y-100)/30;
            xcel=(int)(e.motion.x-(300-(30*(ycel+0.5))))/60 ;
            ycelreal = (float)(e.motion.y-100)/30;
            xcelreal= (e.motion.x-(300-(30*(ycel+0.5))))/60;
            
             if ((ycel>=0 && ycel<=8)&&(xcel>=0 && xcel<=8)){
            seleciono = &celdas[ycel][xcel];
          
            }
            /*point in circle colison:
            sqrt((circle.centerx-entity.x*circle.centerx-entity.x)+(circle.centery-entity.y*circle.centery-entity.y))<=circle.radius

            rec.x = e.motion.x - (int)(rec.w / 2);
            rec.y = e.motion.y - (int)(rec.h / 2);*/
            for (int y=0;y<9;y++){
                    for (int x=0;x<9;x++){
                        if (celdas[y][x].mouse_hit(&e)){
                        celdas[y][x].poligono1[0].color=SDL_Color{0,100,0,255};
                        celdas[y][x].poligono1[1].color=SDL_Color{0,100,0,255};
                        celdas[y][x].poligono1[2].color=SDL_Color{0,100,0,255};
                        }else {
                            celdas[y][x].poligono1[0].color=col;
                            celdas[y][x].poligono1[1].color=col;
                            celdas[y][x].poligono1[2].color=col;
                        }
                    }
                }
        }
        
        /*if (circulo.getcenterx() < rec.x && rec.y + (int)(rec.h / 2) == circulo.getcentery()) {
            if (
                sqrt(pow(circulo.getcenterx() - rec.x, 2) + pow(circulo.getcentery() - (rec.y + (int)(rec.h / 2)), 2))
                <= circulo.getradious()
                )
            {
                r = 255;
                g = 0;
            }
            else
            {
                r = 0;
                g = 255;
            }
        }
        else if (circulo.getcenterx() < rec.x && rec.y > circulo.getcentery()) {
            if (
                sqrt(pow(circulo.getcenterx() - rec.x, 2) + pow(circulo.getcentery() - rec.y, 2))
                <= circulo.getradious()
                )
            {
                r = 255;
                g = 0;
            }
            else
            {
                r = 0;
                g = 255;
            }
        }
        else if (circulo.getcenterx() == rec.x+(int)(rec.w / 2) && rec.y > circulo.getcentery()) {
            if (
                sqrt(pow(circulo.getcenterx() - (rec.x+(int)(rec.w / 2)), 2) + pow(circulo.getcentery() - rec.y , 2))
                <= circulo.getradious()
                )
            {
                r = 255;
                g = 0;
            }
            else
            {
                r = 0;
                g = 255;
            }
        }
        else if (circulo.getcenterx() > rec.x && rec.y > circulo.getcentery()) {
            if (
                sqrt(pow(circulo.getcenterx() - (rec.x + rec.w), 2) + pow(circulo.getcentery() - rec.y, 2))
                <= circulo.getradious()
                )
            {
                r = 255;
                g = 0;
            }
            else
            {
                r = 0;
                g = 255;
            }
        }
        if (circulo.getcenterx() > rec.x && rec.y + (int)(rec.h / 2) == circulo.getcentery()) {
            if (
                sqrt(pow(circulo.getcenterx() - (rec.x+rec.w), 2) + pow(circulo.getcentery() - (rec.y + (int)(rec.h / 2)), 2))
                <= circulo.getradious()
                )
            {
                r = 255;
                g = 0;
            }
            else
            {
                r = 0;
                g = 255;
            }
        }
        if(sqrt(pow(circulo.getcenterx()-mouse_box.getcenterx(),2)+pow(circulo.getcentery()-mouse_box.getcentery(),2))<=(circulo.getradious()+mouse_box.getradious())){
            int a = mouse_box.getcentery();
            mouse_box.sety(a+=5);
            while (sqrt(pow(circulo.getcenterx()-mouse_box.getcenterx(),2)+pow(circulo.getcentery()-mouse_box.getcentery(),2))<=(circulo.getradious()+mouse_box.getradious())){
                if (mouse_box.getcenterx()>circulo.getcenterx()){
                    a = mouse_box.getcenterx();
                    mouse_box.setx(a+=5);
                }else if(mouse_box.getcenterx()<circulo.getcenterx()){
                    a = mouse_box.getcenterx();
                    mouse_box.setx(a-=5);
                } else{
                    mouse_box.setx(445+ (rand() % 10));
                }
            }
        }
        else{
            int a = mouse_box.getcentery();
            mouse_box.sety(a+=5);
        }


        if (mouse_box.getcentery()>400){mouse_box.sety(0);mouse_box.setx(350+ (rand() % 200));}*/

    }
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(pepe_text);
    SDL_FreeSurface(pepe);
    //SDL_DestroyRenderer(texrenderer);
    SDL_FreeSurface(texture_surface);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow( window );
    //Quit SDL subsystems
    SDL_Quit();
    return 0; 
}
