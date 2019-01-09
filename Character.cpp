#include "Character.h"
#include "Coordinate.h"
#include "Match.h"
#include "SDL2/SDL_image.h"
#include "Game.h"
#include <cstdio>

Character::Character()
{
    //ctor
}

Character::~Character()
{
    if(this->surface!=NULL)
        SDL_FreeSurface(this->surface);
}

void Character::loadSurface(){
    string route="images/vectorizados/"+this->image;
    this->surface=SDL_CreateRGBSurface( 0,Game::objSize, Game::objSize, 32, 0, 0, 0, 0 );
    this->surface=IMG_Load(route.c_str());
    SDL_SetColorKey(this->surface, SDL_TRUE, SDL_MapRGB(this->surface->format, 255, 0, 255));
    if(!this->surface)
        printf("No se pudo cargar %s",route.c_str());
}

bool Character::canMoveInThatDirection(char d){

    int logicX;
    int logicY;
    int characterX;
    int characterY;
    switch (d){

        case 'u':
            characterX=this->getX();
            characterY=this->getY()-1;
            logicX=characterX/Game::objSize;
            logicY=(characterY)/Game::objSize;

            if(characterY>=0
                &&characterX%Game::objSize==0
                && Game::match->currentLevel->getWallsMap()[logicY][logicX]!='#')//Si esta dentro y las esquinas coinciden
            {return true;}

            return false;
        break;
        case 'd':
            characterX=this->getX();
            characterY=this->getY();
            logicX=characterX/Game::objSize;
            logicY=(characterY+Game::objSize)/Game::objSize;

            if(characterY<Game::SCREEN_HEIGHT-Game::objSize
                &&characterX%Game::objSize==0
                && Game::match->currentLevel->getWallsMap()[logicY][logicX]!='#')
            {return true;}

            return false;
        break;
        case 'l':
            if(this->getX()==0)
            {
                this->setX(Game::objSize*Game::match->currentLevel->getCols()-Game::objSize+1);
                return true;
            }
            characterX=this->getX()-1;
            characterY=this->getY();
            logicX=characterX/Game::objSize;
            logicY=characterY/Game::objSize;


            if(characterX>=0
                &&characterY%Game::objSize==0
                && Game::match->currentLevel->getWallsMap()[logicY][logicX]!='#')
            {return true;}

            return false;
        break;
        case 'r':

            characterX=this->getX();
            characterY=this->getY();
            logicY=characterY/Game::objSize;
            logicX=(characterX+Game::objSize)/Game::objSize;

            if(characterX==Game::objSize*Game::match->currentLevel->getCols()-Game::objSize)
            {
                this->setX(-1);
                return true;
            }

            if(characterX<Game::GAME_SCREEN_WIDTH-Game::objSize
                &&characterY%Game::objSize==0
                && Game::match->currentLevel->getWallsMap()[logicY][logicX]!='#')
            {return true;}

            return false;
        break;
    }
    return false;
}

void Character::Motion(){

    switch(this->getDirection())
    {
        case 'u':
            if(canMoveInThatDirection('u'))
                this->setY(this->getPosition().getY()-1);
            break;
        case 'd':
            if(canMoveInThatDirection('d'))
                this->setY(this->getPosition().getY()+1);
            break;
        case 'l':
            if(canMoveInThatDirection('l'))
                this->setX(this->getPosition().getX()-1);
            break;
        case 'r':
            if(canMoveInThatDirection('r'))
                this->setX(this->getPosition().getX()+1);
            break;
    }
}
