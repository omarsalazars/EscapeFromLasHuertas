#ifndef CHARACTER_H
#define CHARACTER_H
#include "Coordinate.h"
#include <string>
#include <SDL2/SDL.h>

using namespace std;

class Character
{
    private:
        string image,type,subtype;
        Coordinate position;
        Coordinate startingPosition;
        char direction;
        SDL_Surface* surface;
        int speed;

    public:
        Character();
        virtual ~Character();
        virtual void changeDirection()=0; //Virtual para los cruces
        void loadSurface();
        void Motion();
        bool canMoveInThatDirection(char);
        Uint32 motionCallback(Uint32 interval);
        static Uint32 motionCallback(Uint32 interval,void* param);
        void changePosition();
        ///GET
        string getImage(){return this->image;}
        string getType(){return this->type;}
        string getSubtype(){return this->subtype;}
        Coordinate getPosition(){return this->position;}
        Coordinate getStartingPosition(){return this->startingPosition;}
        char getDirection(){return this->direction;}
        SDL_Surface* getSurface(){return this->surface;}
        int getX(){return this->getPosition().getX();}
        int getY(){return this->getPosition().getY();}
        int getSpeed(){return this->speed;}
        ///SET
        void setSpeed(int speed){this->speed=speed;}
        void setImage(string image){this->image=image;}
        void setType(string type){this->type=type;}
        void setSubtype(string subtype){this->subtype=subtype;}
        void setPosition(Coordinate position){this->position=position;}
        void setStartingPosition(Coordinate startingPosition){this->startingPosition=startingPosition;}
        void setX(int x){this->position.setX(x);}
        void setY(int y){this->position.setY(y);}
        void setDirection(char direction){this->direction=direction;}
        void setSurface(SDL_Surface* surface){this->surface=surface;}
};
#endif // CHARACTER_H
