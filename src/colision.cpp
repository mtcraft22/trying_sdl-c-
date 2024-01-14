#include <circle.hpp>
#include <colison.hpp>

#include <map>
#include <stdexcept>
#include <string>


map<string, Circle_colison*> Circle_ColisionDB = map<string, Circle_colison*>();
map<string, Rect_colison*> Rect_ColisionDB = map<string, Rect_colison*>();


bool col_rect_circ(Circle* circulo , SDL_Rect* rec){
    
        if (circulo->getcenterx() < rec->x && rec->y + (int)(rec->h / 2) == circulo->getcentery()) {
            if (
                sqrt(pow(circulo->getcenterx() - rec->x, 2) + pow(circulo->getcentery() - (rec->y + (int)(rec->h / 2)), 2))
                <= circulo->getradious()
                )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (circulo->getcenterx() < rec->x && rec->y > circulo->getcentery()) {
            if (
                sqrt(pow(circulo->getcenterx() - rec->x, 2) + pow(circulo->getcentery() - rec->y, 2))
                <= circulo->getradious()
                )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (circulo->getcenterx() == rec->x+(int)(rec->w / 2) && rec->y > circulo->getcentery()) {
            if (
                sqrt(pow(circulo->getcenterx() - (rec->x+(int)(rec->w / 2)), 2) + pow(circulo->getcentery() - rec->y , 2))
                <= circulo->getradious()
                )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (circulo->getcenterx() > rec->x && rec->y > circulo->getcentery()) {
            if (
                sqrt(pow(circulo->getcenterx() - (rec->x + rec->w), 2) + pow(circulo->getcentery() - rec->y, 2))
                <= circulo->getradious()
                )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (circulo->getcenterx() > rec->x && rec->y + (int)(rec->h / 2) == circulo->getcentery()) {
            if (
                sqrt(pow(circulo->getcenterx() - (rec->x+rec->w), 2) + pow(circulo->getcentery() - (rec->y + (int)(rec->h / 2)), 2))
                <= circulo->getradious()
                )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    return false;
}


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
SDL_Rect* Rect_colison::get_box(){return this->box;}
bool Rect_colison::oncolision(string tag){
    try {
        Rect_colison* box2detec = Rect_ColisionDB.at(tag);
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
       
        try{
            Circle_colison *box2detec  =  Circle_ColisionDB.at(tag);
            return col_rect_circ(box2detec->get_box(), this->box);
        }catch(std::out_of_range){
            return false; 
        }
        return false;
    }   
}

Circle_colison::Circle_colison(string tag, Circle* box):Colison(tag){
    this->box=box; 
    Circle_ColisionDB[this->tag]=this;
      
}
Circle * Circle_colison::get_box(){return this->box;}
bool Circle_colison::oncolision(string tag){
    try{
        
        Circle_colison *box2detec  =  Circle_ColisionDB.at(tag);
        return pow(box2detec->box->getcenterx()-this->box->getcenterx(),2)+pow(box2detec->box->getcentery()-this->box->getcentery(),2)<=(box2detec->box->getradious()+this->box->getradious())*(box2detec->box->getradious()+this->box->getradious());
    }catch (std::out_of_range){
        try{
            Rect_colison *box2detec  =  Rect_ColisionDB.at(tag);
            return col_rect_circ(this->box, box2detec->get_box());
        }catch(std::out_of_range){
            return false; 
        }
        return false;
    }   
}
void Circle_colison::debug(SDL_Renderer * renderer){
    this->box->DrawCircle(renderer);
}