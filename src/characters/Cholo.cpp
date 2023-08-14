#include "../../include/Cholo.h"
#include "../../include/Match.h"
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Cholo::Cholo()
{
}

Cholo::~Cholo()
{
    for(int i=0;i<2;i++)
    {
        if(this->surfaces[i])
            SDL_FreeSurface(this->surfaces[i]);
    }
}

void Cholo::loadFrightenedSurface()
{
    this->surfaces=new SDL_Surface*[2];
    this->surfaces[0]=this->getSurface();
    string frightenedImage="images/vectorizados/f"+this->getImage();
    this->surfaces[1]=IMG_Load(frightenedImage.c_str());
}

void Cholo::toggleSurface()
{
    if(this->getSurface()==this->surfaces[0])
        this->setSurface(this->surfaces[1]);
    else
        this->setSurface(this->surfaces[0]);
}

void Cholo::changeDirection()
{
    int tx = this->getTarget().getX();
    int ty = this->getTarget().getY();

    int cx = this->getX();
    int cy = this->getY();

    Coordinate dir[3];
    Coordinate aux;
    switch(this->getDirection())
    {
        case UP:
        ///UP
        aux.setY(-1);
        aux.setX(0);
        dir[0] = aux;
        ///RIGHT
        aux.setY(0);
        aux.setX(1);
        dir[1] = aux;
        ///LEFT
        aux.setY(0);
        aux.setX(-1);
        dir[2] = aux;
        break;
        case DOWN:
        ///DOWN
        aux.setY(1);
        aux.setX(0);
        dir[0] = aux;
        ///RIGHT
        aux.setY(0);
        aux.setX(1);
        dir[1] = aux;
        ///LEFT
        aux.setY(0);
        aux.setX(-1);
        dir[2] = aux;
        break;
        case LEFT:
        aux.setY(1);
        aux.setX(0);
        dir[0] = aux;

        aux.setY(-1);
        aux.setX(0);
        dir[1] = aux;

        aux.setY(0);
        aux.setX(-1);
        dir[2] = aux;
        break;
        case RIGHT:
        aux.setY(1);
        aux.setX(0);
        dir[0] = aux;

        aux.setY(-1);
        aux.setX(0);
        dir[1] = aux;

        aux.setY(0);
        aux.setX(1);
        dir[2] = aux;
        break;
    }

    double men = 1000000000000;
    double dis;
    int posmen;
    Direction newDirection;

    for(int i=0; i<=2; i++)
    {
        double suma = ((tx-(cx+dir[i].getX()))*(tx-(cx+dir[i].getX())))
                    + ((ty-(cy+dir[i].getY()))*(ty-(cy+dir[i].getY())));


        dis=sqrt(suma);
        if(dir[i].getX()== 1 && dir[i].getY()==0)
        newDirection = RIGHT;
        if(dir[i].getX()== -1 && dir[i].getY()==0)
        newDirection = LEFT;
        if(dir[i].getX()== 0 && dir[i].getY()==-1)
        newDirection = UP;
        if(dir[i].getX()== 0 && dir[i].getY()==1)
        newDirection = DOWN;

        if(dis<men && this->canMoveInThatDirection(newDirection))
        {
            men = dis;
            posmen=i;
        }
    }

    Coordinate newPosition=dir[posmen];

    if(newPosition.getX()== 1 && newPosition.getY()==0)
        this->setDirection(RIGHT);
    if(newPosition.getX()== -1 && newPosition.getY()==0)
        this->setDirection(LEFT);
    if(newPosition.getX()== 0 && newPosition.getY()==-1)
        this->setDirection(UP);
    if(newPosition.getX()== 0 && newPosition.getY()==1)
        this->setDirection(DOWN);
}

void Cholo::changeStatus()
{
    if(this->getStatus() == ATTACK)
    {
        SDL_AddTimer( 6 * 1000, changeStatusCallback,this);
        this->setStatus(DEFENSE);
            this->setTarget(this->getHidingPosition());
            switch(this->getDirection())
            {
                case LEFT:
                    this->setDirection(RIGHT);
                    break;
                case RIGHT:
                    this->setDirection(LEFT);
                    break;
                case UP:
                    this->setDirection(DOWN);
                    break;
                case DOWN:
                    this->setDirection(UP);
                    break;
            }
    }
    else
    {
        this->setStatus(ATTACK);
        this->toggleSurface();
    }
}

Uint32 Cholo::changeStatusCallback(Uint32 interval,void* param){
    return ((Cholo *) param)->changeStatusCallback(interval);
}
Uint32 Cholo::changeStatusCallback(Uint32 interval)
{
    this->changeStatus();
    return 0;
}
