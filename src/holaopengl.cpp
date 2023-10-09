#include <iostream>
#include <math.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#include <setup.hpp>
#include <grid.hpp>
#include <circle.hpp>
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
    
    SDL_Surface* texture_surface = IMG_Load("./resources/bueno.png");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderizador, texture_surface);

    //cargamos al personaje pricipal

    SDL_Surface* pepe = IMG_Load("./resources/pepe.png");
    SDL_Texture* pepe_text = SDL_CreateTextureFromSurface(renderizador, pepe);
    //caragamos la textura de la segunda capa
    SDL_Surface* segunda_capa = IMG_Load("./resources/ladrillo.png");
    SDL_Texture* capa2_text = SDL_CreateTextureFromSurface(renderizador, segunda_capa);
    if (!tex){cout<<"sdl_texture_load"<<SDL_GetError()<<std::endl;}
    
    SDL_Color col{ 0xff,0xff,0xff,0xff };

    SDL_Point root;

    root ={100,100};
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

    
    root ={110,110};
    terreno celda10 = terreno(60,root,col);
    root ={171,110};
    terreno celda12 = terreno(60,root,col);
    root ={232,110};
    terreno celda13 = terreno(60,root,col);

    root ={80,141};
    terreno celda14 = terreno(60,root,col);
    root ={141,141};
    terreno celda15 = terreno(60,root,col);
    root ={202,141};
    terreno celda16 = terreno(60,root,col);

    root ={50,172};    
    terreno celda17 = terreno(60,root,col);
    root ={111,172};
    terreno celda18 = terreno(60,root,col);
    root ={171,172};
    terreno celda19 = terreno(60,root,col);

    SDL_Event e;    
    bool quit = false;
    celda2.set_ayacent(RIGHT, &celda3);
    celda2.set_ayacent(LEFT, &celda);
    celda5.set_ayacent(RIGHT, &celda6);
    celda5.set_ayacent(TOP, &celda2);
    celda5.set_ayacent(BOTTOM, &celda8);
    celda5.set_ayacent(LEFT, &celda4);
    celda8.set_ayacent(LEFT, &celda7);
    celda8.set_ayacent(RIGHT, &celda9);
    SDL_Vertex pepe_forma[3]={
        {200,200,col,0.0f,0.0f},
        {250,200,col,1.0f,0.0f},
        {200,250,col,0.0f,1.0f}

        };
    SDL_Vertex pepe_forma2[3]={
        {200,250,col,0.0f,1.0f},
        {250,250,col,1.0f,1.0f},
        {250,200,col,1.0f,0.0f}

        };
    int indices_pepe[4]= {0,1,2};
    const SDL_Rect rec={20,20,50,50};

    SDL_MouseMotionEvent mouse;
    Circle circulo = Circle(350,100,80);
    Circle mouse_box = Circle(0,0,25);
    while( quit == false ){
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 255, 0,255);

        celda10.draw(renderizador, capa2_text);
        celda12.draw(renderizador, capa2_text);
        celda13.draw(renderizador, capa2_text);
        celda14.draw(renderizador, capa2_text);
        celda15.draw(renderizador, capa2_text);
        celda16.draw(renderizador, capa2_text);
        celda17.draw(renderizador, capa2_text);
        celda18.draw(renderizador, capa2_text);
        celda19.draw(renderizador, capa2_text);

        celda.draw(renderizador, capa2_text);
        celda2.draw(renderizador, tex);
        celda3.draw(renderizador, tex);
        celda4.draw(renderizador, tex);
        celda5.draw(renderizador, tex);
        celda6.draw(renderizador, tex);
        celda7.draw(renderizador, tex);
        celda8.draw(renderizador, tex);
        celda9.draw(renderizador, capa2_text);

     
        SDL_RenderDrawRect(renderizador, &rec);

        SDL_RenderGeometry(renderizador, pepe_text, pepe_forma, 3, indices_pepe, 3);
        SDL_RenderGeometry(renderizador, pepe_text, pepe_forma2, 3, indices_pepe, 3);
        circulo.DrawCircle(renderizador);
        //mouse_box.DrawCircle(renderizador);
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
            
            if (e.motion.y>=20 && e.motion.y<=70&&e.motion.x>=20 && e.motion.x<=70){
                cout<<"recthit"<<endl;
            }
            /*point in circle colison: 
            sqrt((circle.centerx-entity.x*circle.centerx-entity.x)+(circle.centery-entity.y*circle.centery-entity.y))<=circle.radius*/
            
            else if(sqrt(((350-e.motion.x)*(350-e.motion.x))+((100-e.motion.y)*(100-e.motion.y)))<=80){
                cout << "hitcirc"<<endl;
            }
            else {
                cout<<"nohit"<<endl;
            }
            mouse_box.setx(e.motion.x);
            mouse_box.sety(e.motion.y);
        } 
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
