
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <iostream>
#include <setup.hpp>
#include <grid.hpp>
using namespace std;

int main(void){
    if(!init_sdl()){
        cout << SDL_GetError();
        return -1;
    }
    SDL_Window *window;
    window=make_window_();
    if(!window){
        cout<<"No se inició pantalla" << SDL_GetError();
        return -1;
    }
    SDL_Renderer* renderizador = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Renderer* texrenderer =  SDL_CreateRenderer(window, 2, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //SDL_Renderer* textura =  SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Surface * texture_surface = IMG_Load("./resources/bueno.png");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderizador, texture_surface);
    if (!tex){cout<<"java.sdl.texture.load.creatre"<<SDL_GetError()<<std::endl;}
    
    SDL_Color col{ 0xff,0xff,0xff,0xff };

    SDL_Point root ={100,100};
    terreno celda = terreno(60,root,col);
    root ={161,100};
    terreno celda2 = terreno(60,root,col);
    root ={222,100};
    terreno celda3 = terreno(60,root,col);

    root ={70,131};
    terreno celda4 = terreno(60,root,col);
    root ={131,131};
    terreno celda5 = terreno(60,root,col);
    root ={192,131};
    terreno celda6 = terreno(60,root,col);

    root ={40,162};    
    terreno celda7 = terreno(60,root,col);
    root ={101,162};
    terreno celda8 = terreno(60,root,col);
    root ={161,162};
    terreno celda9 = terreno(60,root,col);

    SDL_Event e;    
    bool quit = false;
    celda5.set_ayacent(RIGHT, &celda6);
    celda5.set_ayacent(TOP, &celda2);
    celda5.set_ayacent(BOTTOM, &celda8);
    celda5.set_ayacent(LEFT, &celda4);
    while( quit == false ){
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 255, 0,255);
        celda.draw(renderizador, tex);
        celda2.draw(renderizador, tex);
        celda3.draw(renderizador, tex);
        celda4.draw(renderizador, tex);
        celda5.draw(renderizador, tex);
        celda6.draw(renderizador, tex);
        celda7.draw(renderizador, tex);
        celda8.draw(renderizador, tex);
        celda9.draw(renderizador, tex);
    
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0,255);
        SDL_RenderPresent(renderizador);
        
        while(SDL_PollEvent( &e ))
        { 
            if( e.type == SDL_QUIT ) {quit = true;}
            else if (e.type == SDL_KEYDOWN) {
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
            }
        } 
    }
    
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(texrenderer);
    SDL_FreeSurface(texture_surface);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow( window );
    //Quit SDL subsystems
    SDL_Quit();
    return 0;
        
}
