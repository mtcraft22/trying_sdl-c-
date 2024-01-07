#include <colison.hpp>
#include <map>
#include <stdexcept>
#include <string>


map<int, Circle_colison*> Circle_ColisionDB = map<int, Circle_colison*>();
map<int, Rect_colison*> Rect_ColisionDB = map<int, Rect_colison*>();


void insert_Circle_colision(int hash, Circle_colison* colision){
    Circle_ColisionDB[hash]=colision;
}

int hash_colision(string colision_tag){
    int hash = 0;
    for (char i : colision_tag){
        hash += i;
        hash = (hash*i)%20;
    }
    return hash;
}

Colison::Colison(string tag){
    this->tag=tag;
}
string Colison::get_tag(){
    return this->tag;
}
Rect_colison::Rect_colison(string tag, SDL_Rect* box):Colison(tag){
    this->tag=tag;
    Rect_ColisionDB[hash_colision(this->tag)]=this;
}
bool Rect_colison::oncolision(SDL_Rect *box2detec){
    return false;
}
bool Rect_colison::oncolision(Circle *box2detec){
    return false;
}
Circle_colison::Circle_colison(string tag, Circle* box):Colison(tag){
    this->box=box; 
    Circle_ColisionDB[hash_colision(this->tag)]=this;
      
}
bool Circle_colison::oncolision(string tag){
    try{
        Circle_colison *box2detec  =  Circle_ColisionDB[hash_colision(tag)];
        return sqrt(pow(box2detec->box->getcenterx()-this->box->getcenterx(),2)+pow(box2detec->box->getcentery()-this->box->getcentery(),2))<=(box2detec->box->getradious()+this->box->getradious());
    }catch (std::out_of_range){
        return false;
    }   
}
void Circle_colison::debug(SDL_Renderer * renderer){
    this->box->DrawCircle(renderer);
}