#include "Bayron.h"
#include "Match.h"
#include "Game.h"

Bayron::Bayron()
{
    this->setImage("cholo3.png");
    this->setDirection('l');
    this->loadSurface();
    this->setHidingPosition(Coordinate(0,600));
    this->setStatus("attack");
    this->setSpeed(100);
    this->loadFrightenedSurface();
}

Bayron::~Bayron()
{
    //dtor
}

void Bayron::changeTarget(){
    Coordinate newTarget;
    char principalDirection;

    Coordinate principalPosition=Game::match->principal->getPosition();
    newTarget = principalPosition;


    principalDirection = Game::match->principal->getDirection();
    switch(principalDirection)
    {
        case 'u':
        for(int i=4; i>=0; i--)
        {
                if(principalPosition.getY()+i*Game::objSize>=0){
                    newTarget.setY(principalPosition.getY()-i*Game::objSize);
                    break;
                }
        }
        break;

        case 'd':
        for(int i=4; i>=0; i--)
        {
                if(principalPosition.getY()-i*Game::objSize<=Game::SCREEN_HEIGHT){
                    newTarget.setY(principalPosition.getY()+i*Game::objSize);
                    break;
                }
        }
        break;
        case'l':
        for(int i=4; i>=0; i--)
        {
                if(principalPosition.getX()+i*Game::objSize>=0){
                    newTarget.setX(principalPosition.getX()-i*Game::objSize);
                    break;
                }
        }
        break;
        case'r':
            for(int i=4; i>=0; i--)
            {
                    if(principalPosition.getX()-i*Game::objSize<=Game::GAME_SCREEN_WIDTH){
                        newTarget.setX(principalPosition.getY()+i*Game::objSize);
                        break;
                    }
            }
        break;
    }

    this->setTarget(newTarget);
}
