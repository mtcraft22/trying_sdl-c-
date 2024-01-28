#include <physics.hpp>

vector2D::vector2D(int x, int y){
        this->x = x;
        this->y = y;
}
int vector2D::sum (){return this->x + this->y;}
int vector2D::gety(){return this->y;}
int vector2D::getx(){return this->x;}
void vector2D::sety(int y){this->y = y;}
void vector2D::vector2D::setx(int x){this->x = x;}

Entity::Entity(int mass,int x, int y){
    this->mass = mass;
    this->pos.setx(x);
    this->pos.sety(y);
}
vector2D Entity::getpos(){return  this->pos;}
void Entity::addforce(vector2D force){

    this->aceleration.setx( force.getx() / this->mass);
    this->aceleration.sety( force.gety() / this->mass);

    this->velocity.setx(this->velocity.getx()+aceleration.getx());
    this->velocity.sety(this->velocity.gety()+aceleration.gety());

    this->pos.setx(this->pos.getx()+this->velocity.getx());
    this->pos.sety(this->pos.gety()+this->velocity.gety());
    
}