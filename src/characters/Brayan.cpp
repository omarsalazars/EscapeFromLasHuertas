#include "../../include/Brayan.h"
#include "../../include/Match.h"
#include "../../include/Game.h"

Brayan::Brayan()
{
    this->setImage("cholo1.png");

    this->setDirection(RIGHT);
    this->loadSurface();
    this->setHidingPosition(Coordinate(1,1));
    this->setStatus(ATTACK);
    this->setSpeed(100);
    this->loadFrightenedSurface();
}

Brayan::~Brayan()
{

}

void Brayan::changeTarget(){
    Coordinate newTarget;
    newTarget=Game::match->principal->getPosition();
    this->setTarget(newTarget);
}
