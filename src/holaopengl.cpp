
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <chunck.hpp>   
#include <setup.hpp>
#include <circle.hpp>
#include <colison.hpp>



using namespace std;

#define sdl_ticks_4_frame 1000/30.0

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
    SDL_Surface* texture_awita = IMG_Load("./resources/awita.png");
    
    SDL_Texture* awita = SDL_CreateTextureFromSurface(renderizador, texture_awita);
    SDL_Texture* tex = IMG_LoadTexture (renderizador, "./resources/bueno.png");
   

    
    //cargamos awita
   
    //cargamos al personaje principal
    SDL_Surface* pepe = IMG_Load("./resources/pepe.png");
    SDL_Texture* pepe_text = SDL_CreateTextureFromSurface(renderizador, pepe);
    //cargamos la textura de la segunda capa
    SDL_Surface* segunda_capa = IMG_Load("./resources/ladrillo.png");
    SDL_Texture* capa2_text = SDL_CreateTextureFromSurface(renderizador, segunda_capa);
    if (!tex) { cout << "sdl_texture_load" << SDL_GetError() << std::endl; }

    SDL_Color col{ 0xff,0xff,0xff,0xff };

    Chunck* trozo = new Chunck(40,10,10, 300,100,&col);
   
    
    SDL_Vertex vertical_grid[4] = {
        {300,100,col,0.0f,0.0f},
        {340,140,col,1.0f,0.0f},
        {340,120,col,1.0f,1.0f},
        /*{0,0,col,0.0f,0.0f},
        {0,0,col,0.0f,0.0f},
        {0,0,col,0.0f,0.0f},*/
    };



    
    
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
    
    terreno * seleciono = trozo->gridgroup.at(1).at(1);
    Circle bolita = Circle(800,100, 10);
    Circle bolita2 = Circle(800,175, 25);
    int start = SDL_GetTicks();
    int end = SDL_GetTicks();
    double delta = 0.0;

    Circle_colison mouse_box_col = Circle_colison("mouse_box",&mouse_box);
    Circle_colison bolita_col = Circle_colison("bolita",&bolita);
    Circle_colison bolita_2_col  = Circle_colison("bolita2",&bolita2);
    
    
    while (!quit) {

        start = SDL_GetTicks();
        delta = start - end;
        
        if (delta>sdl_ticks_4_frame){
            end = start;
            cout << "frames: " << 1000/delta  << std::endl ;
            SDL_RenderClear(renderizador);
            SDL_SetRenderDrawColor(renderizador, r,g,b,a);
            if (mouse_box_col.oncolision("bolita")&& !mouse_box_col.oncolision("bolita2")){
                SDL_SetRenderDrawColor(renderizador, 255, 0, 0,255);
            }else if (mouse_box_col.oncolision("bolita2")&& !mouse_box_col.oncolision("bolita")){
                SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 255);
            }else if (mouse_box_col.oncolision("bolita2")&&mouse_box_col.oncolision("bolita")){
                SDL_SetRenderDrawColor(renderizador, 255, 0, 255, 255);
            }else{
                SDL_SetRenderDrawColor(renderizador, r,g,b,a);
            }
            
            trozo->draw_chunk(renderizador, tex);
            bolita.setradious(25);
            bolita.DrawCircle(renderizador);
            bolita2.DrawCircle(renderizador);
            mouse_box.DrawCircle(renderizador);
            
            //SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255);
            /*for (int i = bolita.getradious()-1; i>=0; i--){
                Circle bolita2 = Circle(bolita.getcenterx(),bolita.getcentery(),i);
                bolita2.DrawCircle(renderizador);
            }*/
            SDL_RenderPresent(renderizador);
            SDL_SetRenderDrawColor(renderizador,0,0,0,255);

            mouse_box.setx(mx);
            mouse_box.sety(my);
            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT) { 
                    quit = true; 
                }
                else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym){
                        case SDLK_d:
                            if (seleciono->point_hit(bolita.getcenterx(), bolita.getcentery())) {
                                bolita.sety(bolita.getcenterx() + 1);
                            }
                            seleciono->move(TOP_RIGHT, 1, 0);
                            seleciono->move(TOP_LEFT, 1, 0);
                            seleciono->move(BOTTOM_LEFT, 1, 0);
                            seleciono->move(BOTTOM_RIGHT, 1, 0);
                            break;
                        case SDLK_a:
                            if (seleciono->point_hit(bolita.getcenterx(), bolita.getcentery())) {
                                bolita.sety(bolita.getcenterx() - 1);
                            }
                            seleciono->move(TOP_RIGHT, -1, 0);
                            seleciono->move(TOP_LEFT, -1, 0);
                            seleciono->move(BOTTOM_LEFT, -1, 0);
                            seleciono->move(BOTTOM_RIGHT, -1, 0);
                            break;
                        case SDLK_s:
                            if (seleciono->point_hit(bolita.getcenterx(), bolita.getcentery())) {
                            
                                bolita.sety(bolita.getcentery() + 1);
                            }
                            seleciono->move(TOP_RIGHT, 0, 1);
                            seleciono->move(TOP_LEFT, 0, 1);
                            seleciono->move(BOTTOM_LEFT, 0, 1);
                            seleciono->move(BOTTOM_RIGHT, 0, 1);
                            
                            break;
                        case SDLK_w:
                            if (seleciono->point_hit(bolita.getcenterx(), bolita.getcentery())) {
                                bolita.sety(bolita.getcentery() - 1);
                            }
                            seleciono->move(TOP_RIGHT, 0, -1);
                            seleciono->move(TOP_LEFT, 0, -1);
                            seleciono->move(BOTTOM_LEFT, 0, -1);
                            seleciono->move(BOTTOM_RIGHT, 0, -1);
                            break;
                        default:
                            break;
                    }
                }
                else if (e.type==SDL_MOUSEWHEEL) {
                    if (e.wheel.y < 0) {
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
            for (vector<terreno *> i: trozo->gridgroup ){
                for (terreno *ter: i){
                    if (ter->point_hit(mx, my)) {
                        ter->poligono1[0].color = SDL_Color{ 0,100,0,255 };
                        ter->poligono1[1].color = SDL_Color{ 0,100,0,255 };
                        ter->poligono1[2].color = SDL_Color{ 0,100,0,255 };
                        ter->poligono2[0].color = SDL_Color{ 0,100,0,255 };
                        ter->poligono2[1].color = SDL_Color{ 0,100,0,255 };
                        ter->poligono2[2].color = SDL_Color{ 0,100,0,255 };
                        seleciono = ter;
                    }
                    else if (ter->point_hit(bolita.getcenterx(), bolita.getcentery())) {
                        ter->poligono1[0].color = SDL_Color{ 100,0,0,255 };
                        ter->poligono1[1].color = SDL_Color{ 100,0,0,255 };
                        ter->poligono1[2].color = SDL_Color{ 100,0,0,255 };
                        ter->poligono2[0].color = SDL_Color{ 100,0,0,255 };
                        ter->poligono2[1].color = SDL_Color{ 100,0,0,255 };
                        ter->poligono2[2].color = SDL_Color{ 100,0,0,255 };
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
                    else 
                    {
                        ter->poligono1[0].color = col;
                        ter->poligono1[1].color = col;
                        ter->poligono1[2].color = col;
                        ter->poligono2[0].color = col;
                        ter->poligono2[1].color = col;
                        ter->poligono2[2].color = col;
                    }
                
                }

            }
        }else{
            SDL_Delay(floor(sdl_ticks_4_frame-delta));
        }
    }
    
    delete trozo;
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(pepe_text);
    
    SDL_FreeSurface(pepe);
    //SDL_DestroyRenderer(texrenderer);
    
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow( window );
    //Quit SDL subsystems
    SDL_Quit();
    return 0; 
}
