#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
    private:
    int x,y;
    public:
        Coordinate();
        Coordinate(int, int);
        virtual ~Coordinate();
        ///GET Y SET
        int getX(){return this->x;}
        int getY(){return this->y;}
        void setX(int x){this->x=x;}
        void setY(int y){this->y=y;}
        void setCoordinate(Coordinate c){this->x=c.getX();this->y=c.getY();}
        ///FIN GET Y SET
};

#endif // COORDINATE_H
