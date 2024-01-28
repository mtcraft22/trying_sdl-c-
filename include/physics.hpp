class vector2D {
    public:
    vector2D(int x, int y);
    int sum ();
    int gety();
    int getx();
    void sety(int y);
    void setx(int x);
    private:
        int x,y;

};

class Entity {
    private:
        int mass;
        vector2D pos = vector2D(0,0);
        vector2D aceleration = vector2D(0,0);
        vector2D velocity = vector2D(0,0);
    public:
        Entity(int mass,int x, int y);
        vector2D getpos();
        void addforce (vector2D force);
    
};