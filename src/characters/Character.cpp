#include "../../include/Character.h"
#include "../../include/Coordinate.h"
#include "../../include/Match.h"
#include <SDL2/SDL_image.h>
#include "../../include/Game.h"

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

bool Character::canMoveInThatDirection(Direction direction){

    int logicX;
    int logicY;
    int characterX;
    int characterY;
    switch (direction){

        case UP:
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
        case DOWN:
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
        case LEFT:
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
        case RIGHT:

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
        case UP:
            if(canMoveInThatDirection(UP))
                this->setY(this->getPosition().getY()-1);
            break;
        case DOWN:
            if(canMoveInThatDirection(DOWN))
                this->setY(this->getPosition().getY()+1);
            break;
        case LEFT:
            if(canMoveInThatDirection(LEFT))
                this->setX(this->getPosition().getX()-1);
            break;
        case RIGHT:
            if(canMoveInThatDirection(RIGHT))
                this->setX(this->getPosition().getX()+1);
            break;
    }
}
