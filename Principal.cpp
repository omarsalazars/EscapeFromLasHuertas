#include "Principal.h"
#include "Match.h"
#include <cstdio>
#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Principal::Principal()
{
    this->setImage("cholo1.png");
    this->setScore(0);
    this->setX(9*Game::objSize);
    this->setY(13*Game::objSize);
    this->setStartingPosition(Coordinate(8*Game::objSize,13*Game::objSize));
    this->setDirection('r');
    this->loadSurface();
    this->setSpeed(5);
    this->lives.push("cartera");
    this->lives.push("celular");
    this->lost=false;
}

Principal::~Principal()
{
    //dtor
}

void Principal::changeDirection(){
    switch(Game::event->key.keysym.sym)
    {
        case SDLK_UP:
            this->setDirection('u');
            break;
        case SDLK_DOWN:
            this->setDirection('d');//down
            break;
        case SDLK_LEFT:
            this->setDirection('l');//left
            break;
        case SDLK_RIGHT:
            this->setDirection('r');
    }
}

void Principal::respawn()
{
    if(this->lives.size()==0)
    {
        this->lost=true;
        SDL_Delay(1000);
        return;
    }
    string route="images/vectorizados/"+this->lives.top()+".png";
    this->lives.pop();
    bool drawn=false;
    SDL_Surface* vida=SDL_CreateRGBSurface( 0,Game::objSize, Game::objSize, 32, 0, 0, 0, 0 );
    SDL_SetColorKey(vida, SDL_TRUE, SDL_MapRGB(vida->format, 255, 0, 255));
    vida=IMG_Load(route.c_str());
    SDL_Rect vidaRect;
    for(int i=Game::match->currentLevel->getRows()-1;i>=0 ;i--){

        for(int j=Game::match->currentLevel->getCols()-1; j>=0 ;j--){
            if(Game::match->currentLevel->getCollectedItems()[i][j])
            {
                Game::match->currentLevel->setItemBool(i,j);
                vidaRect.x = j*Game::objSize;
                vidaRect.y = i*Game::objSize;
                vidaRect.w = Game::objSize;
                vidaRect.h = Game::objSize;
                SDL_BlitScaled(vida,NULL,Game::match->currentLevel->getBackgroundSurface(),&vidaRect);
                drawn=true;

                Game::match->currentLevel->setItemInMap(i,j,'v');
                break;
            }

        }
        if(drawn){break;}

    }

}
Uint32 Principal::respawnLifeCallback(Uint32 interval,void* param){
    return ((Cholo *) param)->changeStatusCallback(interval);
}
Uint32 Principal::respawnLifeCallback(Uint32 interval)
{
    this->lives.pop();
    return 0;
}
