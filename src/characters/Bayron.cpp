#include "../../include/Bayron.h"
#include "../../include/Match.h"
#include "../../include/Game.h"

Bayron::Bayron()
{
    this->setImage("cholo3.png");
    this->setDirection(LEFT);
    this->loadSurface();
    this->setHidingPosition(Coordinate(0,600));
    this->setStatus(ATTACK);
    this->setSpeed(100);
    this->loadFrightenedSurface();
}

Bayron::~Bayron()
{
    //dtor
}

void Bayron::changeTarget(){
    Coordinate newTarget;
    Direction principalDirection;

    Coordinate principalPosition=Game::match->principal->getPosition();
    newTarget = principalPosition;


    principalDirection = Game::match->principal->getDirection();
    switch(principalDirection)
    {
        case UP:
        for(int i=4; i>=0; i--)
        {
                if(principalPosition.getY()+i*Game::objSize>=0){
                    newTarget.setY(principalPosition.getY()-i*Game::objSize);
                    break;
                }
        }
        break;

        case DOWN:
        for(int i=4; i>=0; i--)
        {
                if(principalPosition.getY()-i*Game::objSize<=Game::SCREEN_HEIGHT){
                    newTarget.setY(principalPosition.getY()+i*Game::objSize);
                    break;
                }
        }
        break;
        case LEFT:
        for(int i=4; i>=0; i--)
        {
                if(principalPosition.getX()+i*Game::objSize>=0){
                    newTarget.setX(principalPosition.getX()-i*Game::objSize);
                    break;
                }
        }
        break;
        case RIGHT:
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
