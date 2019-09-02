#include "Cholo.h"
#include "Match.h"
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
        case 'u':
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
        case 'd':
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
        case'l':
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
        case'r':
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
    char newDirection;

    for(int i=0; i<=2; i++)
    {
        double suma = ((tx-(cx+dir[i].getX()))*(tx-(cx+dir[i].getX())))
                    + ((ty-(cy+dir[i].getY()))*(ty-(cy+dir[i].getY())));


        dis=sqrt(suma);
        if(dir[i].getX()== 1 && dir[i].getY()==0)
        newDirection = 'r';
        if(dir[i].getX()== -1 && dir[i].getY()==0)
        newDirection = 'l';
        if(dir[i].getX()== 0 && dir[i].getY()==-1)
        newDirection = 'u';
        if(dir[i].getX()== 0 && dir[i].getY()==1)
        newDirection = 'd';

        if(dis<men && this->canMoveInThatDirection(newDirection))
        {
            men = dis;
            posmen=i;
        }
    }

    Coordinate newPosition=dir[posmen];

    if(newPosition.getX()== 1 && newPosition.getY()==0)
        this->setDirection('r');
    if(newPosition.getX()== -1 && newPosition.getY()==0)
        this->setDirection('l');
    if(newPosition.getX()== 0 && newPosition.getY()==-1)
        this->setDirection('u');
    if(newPosition.getX()== 0 && newPosition.getY()==1)
        this->setDirection('d');
}

void Cholo::changeStatus()
{
    if(this->getStatus()=="attack")
    {
        SDL_AddTimer( 6 * 1000, changeStatusCallback,this);
        this->setStatus("defense");
            this->setTarget(this->getHidingPosition());
            switch(this->getDirection())
            {
                case 'l':
                    this->setDirection('r');
                    break;
                case 'r':
                    this->setDirection('l');
                    break;
                case 'u':
                    this->setDirection('d');
                    break;
                case 'd':
                    this->setDirection('u');
                    break;
            }
    }
    else
    {
        this->setStatus("attack");
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
