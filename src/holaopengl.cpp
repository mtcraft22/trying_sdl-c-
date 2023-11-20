#include "SDL_events.h"
#include "SDL_mouse.h"
#include "SDL_pixels.h"
#include <bits/fs_fwd.h>
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
int mx, my;
int main(int argc, char* argv[]) {
    if (!init_sdl()) {
        cout << SDL_GetError();
        return -1;
    }
    SDL_Window* window;
    window = make_window_();
    if (!window) {
        cout << "No se inició pantalla: " << SDL_GetError();
        return -1;
    }
    SDL_Renderer* renderizador = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* texture_surface = IMG_Load("./resources/bueno.png");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderizador, texture_surface);
    //cargamos awita
   
    //cargamos al personaje principal
    SDL_Surface* pepe = IMG_Load("./resources/pepe.png");
    SDL_Texture* pepe_text = SDL_CreateTextureFromSurface(renderizador, pepe);
    //cargamos la textura de la segunda capa
    SDL_Surface* segunda_capa = IMG_Load("./resources/ladrillo.png");
    SDL_Texture* capa2_text = SDL_CreateTextureFromSurface(renderizador, segunda_capa);
    if (!tex) { cout << "sdl_texture_load" << SDL_GetError() << std::endl; }

    SDL_Color col{ 0xff,0xff,0xff,0xff };

    SDL_Point root;
    root = { 0,0 };
    


    vector<vector<terreno*>> celdas;
    vector<terreno*> celdarow ;

    root = { 550,100 };


    for (int y = 0; y < 15; y++) {
         
        for (int x = 0; x < 15; x++) {
            

            terreno * cel = new terreno(60, root, col);
        
            celdarow.push_back(cel);
            root.x += 60;
        }
        celdas.push_back(celdarow);
        celdarow.clear();
        root.y += 30;
        root.x = 550 - (30 * (y + 1));
    }
    
    for (int y= 0; y<= celdas.size()-1; y++){
        for (int x= 0; x<= celdas.at(y).size()-1; x++){
            if (x+1 <= celdas.at(y).size()-1){
                celdas[y][x]->set_ayacent(RIGHT, celdas[y][x+1]);
            }
            if (y+1 <= celdas.size()-1){
                celdas[y][x]->set_ayacent(BOTTOM, celdas[y+1][x]);
            }
            if (x - 1 >= 0) { 
                celdas[y][x]->set_ayacent(LEFT, celdas[y][x - 1]);
            }
            if (y - 1 >= 0) {
                celdas[y][x]->set_ayacent(TOP, celdas[y-1][x]);
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
 
    float* grid_colision_offsets[2] = { 0,0 };
    
    terreno * seleciono = celdas[0][0];
    Circle bolita = Circle(550+(30*5), 100+(15*5), 10);

    while (!quit) {
        
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, r, g, b, a);
        
        //SDL_SetRenderDrawBlendMode(renderizador,SDL_BLENDMODE_ADD);
        
     
        
        
        
        for (vector<terreno *> i: celdas ){
            for (terreno *ter2: i){
                ter2->draw(renderizador, tex);
                
            }
        }
        SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255);
        
        bolita.DrawCircle(renderizador);
        for (int i = bolita.getradious()-1; i>0; i--){
            Circle bolita2 = Circle(bolita.getcenterx(),bolita.getcentery(),i);
            bolita2.DrawCircle(renderizador);
        }

        SDL_RenderPresent(renderizador);
        SDL_SetRenderDrawColor(renderizador,0,0,0,255);
      
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) { quit = true; }
            else if (e.type == SDL_MOUSEBUTTONDOWN){
                switch (e.button.button) {
                    case SDL_BUTTON_LEFT:
                        for (vector<terreno *> i: celdas ){
                            for (terreno *ter: i){
                                if (ter->point_hit(e.motion.x,e.motion.y)) {
                
                                    seleciono = ter;
                                }
                            }
                        }
                    break;
                    default:
                        break;

                    
                }
                
            }
            else if (e.type==SDL_MOUSEWHEEL) {
                
                if (e.wheel.y < 0){
                    if (seleciono->point_hit(bolita.getcenterx(), bolita.getcentery())){
                        bolita.sety(bolita.getcentery()+1);
                    }
                    seleciono->move(TOP_RIGHT, 0,1);
                    seleciono->move(TOP_LEFT, 0, 1);
                    seleciono->move(BOTTOM_LEFT, 0, 1);
                    seleciono->move(BOTTOM_RIGHT, 0, 1);
                    
                    break;
                }else if (e.wheel.y >0){
                    if (seleciono->point_hit(bolita.getcenterx(), bolita.getcentery())){
                        bolita.sety(bolita.getcentery()-1);
                    }
                    seleciono->move(TOP_RIGHT, 0, -1);
                    seleciono->move(TOP_LEFT, 0, -1);
                    seleciono->move(BOTTOM_LEFT, 0, -1);
                    seleciono->move(BOTTOM_RIGHT, 0, -1);
                    break;
                }
                        
                 
            }
            
            mx = e.motion.x;
            my = e.motion.y;
           
           
            
        }
        
        for (vector<terreno *> i: celdas ){
            for (terreno *ter: i){
               

                    seleciono->poligono1[0].color = SDL_Color{ 0,100,0,255 };
                    seleciono->poligono1[1].color = SDL_Color{ 0,100,0,255 };
                    seleciono->poligono1[2].color = SDL_Color{ 0,100,0,255 };


                if (ter->point_hit(bolita.getcenterx(), bolita.getcentery())) {
                    ter->poligono1[0].color = SDL_Color{ 100,0,0,255 };
                    ter->poligono1[1].color = SDL_Color{ 100,0,0,255 };
                    ter->poligono1[2].color = SDL_Color{ 100,0,0,255 };
                    if (ter->poligono1[0].position.y < ter->poligono1[1].position.y) {
                        bolita.setx(bolita.getcenterx() + 4);
                        bolita.sety(bolita.getcentery() + 1);
                    }
                    else if (ter->poligono1[0].position.y > ter->poligono1[1].position.y) {
                        bolita.setx(bolita.getcenterx() - 4);
                        bolita.sety(bolita.getcentery() + 1);
                    }
                    else if ((ter->poligono1[1].position.y - ter->poligono2[0].position.y > 15) || (ter->poligono1[1].position.y - ter->poligono2[1].position.y > 15)) {
                        bolita.setx(bolita.getcenterx() + 1);
                        bolita.sety(bolita.getcentery() + 4);
                    }
                }
                else {
                    ter->poligono1[0].color = col;
                    ter->poligono1[1].color = col;
                    ter->poligono1[2].color = col;
                }
                
            }
            
        }
        
    }
    for (vector<terreno *> i: celdas ){
        for (terreno *ter: i){
            delete ter;
    }}

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
