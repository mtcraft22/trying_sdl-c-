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
    this->box=box;
    Rect_ColisionDB[this->tag]=this;
}
bool Rect_colison::oncolision(string tag){
    try {
        Rect_colison* box2detec = Rect_ColisionDB[tag];

        int area1 = box2detec->box->h * box2detec->box->w;
        int area2 = this->box->h * this->box->w;

            return 
                (
                    (
                        (
                            box2detec->box->x <= (this->box->x + this->box->w) && box2detec->box->x >= this->box->x
                        )
                        &&
                        (
                            box2detec->box->y <= (this->box->y + this->box->h) && box2detec->box->y >= this->box->y
                        )
                    )
                    ||
                    (
                        (
                            (box2detec->box->x+box2detec->box->w) <= (this->box->x + this->box->w) && (box2detec->box->x+box2detec->box->w) >= this->box->x
                        )
                        &&
                        (
                            (box2detec->box->y+box2detec->box->h) <= (this->box->y + this->box->h) && (box2detec->box->y+box2detec->box->h) >= this->box->y
                        )
                    )
                    ||
                    (
                        (
                            box2detec->box->x <= (this->box->x + this->box->w) && box2detec->box->x >= this->box->x
                        )
                        &&
                        (
                            (box2detec->box->y+box2detec->box->h) <= (this->box->y + this->box->h) && (box2detec->box->y+box2detec->box->h) >= this->box->y
                        )
                    )
                    ||
                    (
                        (
                            (box2detec->box->x+box2detec->box->w) <= (this->box->x + this->box->w) && (box2detec->box->x+box2detec->box->w) >= this->box->x
                        )
                        &&
                        (
                            box2detec->box->y <= (this->box->y + this->box->h) && box2detec->box->y >= this->box->y
                        )
                    )
                    ||
                    (   
                        (
                            this->box->x <= (box2detec->box->x + box2detec->box->w) && this->box->x >= box2detec->box->x
                        )
                        &&
                        (
                            this->box->y <= (box2detec->box->y + box2detec->box->h) && this->box->y >= box2detec->box->y
                        )
                    )
                    ||
                    (
                        (
                            (this->box->x+this->box->w) <= (box2detec->box->x + box2detec->box->w) && (this->box->x+this->box->w) >= box2detec->box->x
                        )
                        &&
                        (
                            (this->box->y+this->box->h) <= (box2detec->box->y + box2detec->box->h) && (this->box->y+this->box->h) >= box2detec->box->y
                        )
                    )
                    ||
                    (
                        (
                            this->box->x <= (box2detec->box->x + box2detec->box->w) && this->box->x >= box2detec->box->x
                        )
                        &&
                        (
                            (this->box->y+box2detec->box->h) <= (box2detec->box->y + box2detec->box->h) && (this->box->y+this->box->h) >= box2detec->box->y
                        )
                    )
                    ||
                    (
                        (
                            (this->box->x+box2detec->box->w) <= (box2detec->box->x + box2detec->box->w) && (this->box->x+this->box->w) >= box2detec->box->x
                        )
                        &&
                        (
                            this->box->y <= (box2detec->box->y + box2detec->box->h) && this->box->y > box2detec->box->y
                        )
                    )
                );
        
    }
    catch (std::out_of_range) {
        return false;
    }
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