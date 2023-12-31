#include <colison.hpp>
#include <map>
#include <stdexcept>
#include <string>


map<string, Circle_colison*> Circle_ColisionDB = map<string, Circle_colison*>();
map<string, Rect_colison*> Rect_ColisionDB = map<string, Rect_colison*>();


Colison::Colison(string tag){
    this->tag=tag;
}
string Colison::get_tag(){
    return this->tag;
}
Rect_colison::Rect_colison(string tag, SDL_Rect* box):Colison(tag){
    this->tag=tag;
    Rect_ColisionDB[this->tag]=this;
}
bool Rect_colison::oncolision(SDL_Rect *box2detec){
    return false;
}
bool Rect_colison::oncolision(Circle *box2detec){
    return false;
}
Circle_colison::Circle_colison(string tag, Circle* box):Colison(tag){
    this->box=box; 
    Circle_ColisionDB[this->tag]=this;
      
}
bool Circle_colison::oncolision(string tag){
    try{
        Circle_colison *box2detec  =  Circle_ColisionDB[tag];
        return sqrt(pow(box2detec->box->getcenterx()-this->box->getcenterx(),2)+pow(box2detec->box->getcentery()-this->box->getcentery(),2))<=(box2detec->box->getradious()+this->box->getradious());
    }catch (std::out_of_range){
        try{
            Rect_colison *box2detec  =  Rect_ColisionDB[tag];
            return false; //TODO: program circle-rectangle colision
        }catch(std::out_of_range){
            return false; 
        }
        return false;
    }   
}
void Circle_colison::debug(SDL_Renderer * renderer){
    this->box->DrawCircle(renderer);
}