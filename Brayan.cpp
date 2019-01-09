#include "Brayan.h"
#include "Match.h"
#include "Game.h"

Brayan::Brayan()
{
    this->setImage("cholo1.png");

    this->setDirection('r');
    this->loadSurface();
    this->setHidingPosition(Coordinate(1,1));
    this->setStatus("attack");
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
