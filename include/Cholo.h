#ifndef CHOLO_H
#define CHOLO_H

#include "Character.h"
#include "Coordinate.h"

enum Status { ATTACK, DEFENSE };

class Cholo : public Character
{
    private:
        Coordinate target;
        Coordinate hidingPosition;
        SDL_Surface** surfaces;
    public:
        Cholo();
        virtual ~Cholo();
        Status status;
        void changeDirection();
        void loadFrightenedSurface();
        void changeStatus();
        virtual void changeTarget()=0;
        void toggleSurface();
        Uint32 changeStatusCallback(Uint32 interval);
        static Uint32 changeStatusCallback(Uint32 interval,void* param);
        ///GET Y SET
        Coordinate getTarget(){return this->target;}
        Coordinate getHidingPosition(){return this->hidingPosition;}
        Status getStatus(){return this->status;}
        void setStatus(Status status){this->status=status;}
        void setTarget(Coordinate target){this->target=target;}
        void setHidingPosition(Coordinate hidingPosition){this->hidingPosition=hidingPosition;}
        ///FIN GET Y SET
};

#endif // CHOLO_H
