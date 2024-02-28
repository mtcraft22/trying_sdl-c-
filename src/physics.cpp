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
vector2D Entity::getaceleration() { return  this->aceleration; }
vector2D Entity::getvelocity() { return  this->velocity; }
vector2D Entity::getforce() { return this->force; };

int Entity::getmass() {
    return this->mass;

}
void Entity::setaceleration(vector2D aceleration) { this->aceleration = aceleration; }
void Entity::setpos(vector2D pos) { this->pos = pos; }
void Entity::setvelocity(vector2D velocity) { this->velocity = velocity; }
void Entity::setforce(vector2D force) { this->force = force; };

void Entity::addforce(vector2D force){
    this->setforce(force);
    this->aceleration.setx( this->force.getx() / this->mass);
    this->aceleration.sety( this->force.gety() / this->mass);
    

    this->velocity.setx(this->velocity.getx() + aceleration.getx() );
    this->velocity.sety(this->velocity.gety() + aceleration.gety() );

    move();
    
}
void Entity::move() {
    int ty, tx = 0 ;
    tx = this->aceleration.getx();
    ty = this->aceleration.gety();
    this->aceleration.setx(tx -= 0.9);
    this->aceleration.sety(ty -= 0.9);

    this->velocity.setx(this->velocity.getx() + aceleration.getx());
    this->velocity.sety(this->velocity.gety() + aceleration.gety());
    if (this->velocity.getx() > 0) {
        this->pos.setx(this->pos.getx() + this->velocity.getx());
    }
    if (this->velocity.gety() > 0) {
        this->pos.sety(this->pos.gety() + this->velocity.gety());
    }
}