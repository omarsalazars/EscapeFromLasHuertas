#include "Nivel.h"
#include <fstream>
#include "Brayan.h"
#include "Kevin.h"
#include "Bayron.h"
#include "Match.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include "Game.h"

using namespace std;
Nivel::Nivel(string file="1"){
    this->backgroundSurface=NULL;
    this->principal=Game::match->principal;

///Obtener matriz de fondo
    string route = file+"/walls.txt";
    this->setTotalItems(0);
    fstream info(route.c_str(), ios::in);
    info >> this->rows>>this->cols;
    this->wallsMap = new char*[this->rows];
    for(int i=0;i<this->rows; i++){wallsMap[i]=new char[this->cols];}

    string row;
    for(int i=0; i<this->rows; i++){
        info>>row;
        for(int j=0; j<this->cols; j++){wallsMap[i][j]=row[j];}
    }
    info.close();

///Obtener matriz de items

    route=file+"/items.txt";
    info.open(route.c_str(), ios::in);
    this->itemsMap = new char*[this->rows];
    for(int i=0;i<this->rows; i++){this->itemsMap[i]=new char[this->cols];}
    for(int i=0; i<this->rows; i++){
        info>>row;
        for(int j=0; j<this->cols; j++)
        {
            this->itemsMap[i][j]=row[j];
        }
    }
    info.close();

///Obtener arreglo de cholos
    string type;
    route=file+"/cholos.txt";
    info.open(route.c_str(), ios::in);
    info >> this->totalCholos;
    this->cholos = new Cholo*[this->totalCholos];
    for(int i=0; i<this->totalCholos; i++){
        info >> type;
        if(type=="Brayan"){this->cholos[i] = new Brayan();}
        if(type=="Kevin"){this->cholos[i] = new Kevin();}
        if(type=="Bayron"){this->cholos[i] = new Bayron();}
    }
    info.close();
///Inicializar matriz de items recogidos y variable de nivel superado
    this->cleared =false;
    this->collectedItems = new bool*[this->rows];
    for(int i=0; i<this->rows; i++){
        this->collectedItems[i] = new bool[this->cols];
        for(int j=0; j<this->cols; j++){
            this->collectedItems[i][j]=false;
        }
    }

    route=file+"/initialPositions.txt";
    info.open(route.c_str(),ios::in);
    string positionsRow;
    for(int i=0;i<this->rows;i++)
    {
        info>>positionsRow;
        for(int j=0;j<this->cols;j++)
        {
            if(positionsRow[j]=='p')
            {
                Game::match->principal->setStartingPosition(Coordinate(j*Game::objSize,i*Game::objSize));
                Game::match->principal->setPosition(Game::match->principal->getStartingPosition());
            }
            else if(isdigit(positionsRow[j]))
            {
                this->cholos[positionsRow[j]-'0']->setStartingPosition(Coordinate(j*Game::objSize,i*Game::objSize));
                this->cholos[positionsRow[j]-'0']->setPosition(this->cholos[positionsRow[j]-'0']->getStartingPosition());
            }
        }
    }
    info.close();
    this->backgroundSurface=this->createBackgroundSurface();

}

void Nivel::initNivel()
{
    Nivel::Surfaces=new SDL_Surface*[11];
    string route="images/grafitis/";
    for(int i=0;i<8;i++)
    {
        stringstream ss;
        ss<<i+1;
        string numstring=ss.str();
        string file=route+"graf"+numstring+".png";
        Nivel::Surfaces[i]=IMG_Load(file.c_str());
        if(!Nivel::Surfaces[i]) printf("No se encontro %s\n",file.c_str());
    }
    string file=route+"calle.png";
    Nivel::Surfaces[8]=IMG_Load(file.c_str());
    if(!Nivel::Surfaces[8]) printf("No se encontro %s\n",file.c_str());

    route="images/vectorizados/";
    file=route+"perla.png";
    Nivel::Surfaces[9]=IMG_Load(file.c_str());
    if(!Nivel::Surfaces[9]) printf("No se encontro %s\n",file.c_str());

    file=route+"caguama.png";
    Nivel::Surfaces[10]=IMG_Load(file.c_str());
    if(!Nivel::Surfaces[10]) printf("No se encontro %s\n",file.c_str());
    /*
    Nivel::Surfaces={
        0 = graf1.png
        1 = graf2.png
        2 = graf3.png
        3 = graf4.png
        4 = graf5.png
        5 = graf6.png
        6 = graf7.png
        7 = graf8.png
        8 = calle.png
        9 = perla.png
        10 = caguama.png
    */
}

///Crear surface de background

SDL_Surface* Nivel::createBackgroundSurface()
{
    SDL_Surface *backgroundSurface = SDL_CreateRGBSurface(0,Game::GAME_SCREEN_WIDTH,Game::SCREEN_HEIGHT,32,0,0,0,0);
    SDL_Rect backgroundRect;
    SDL_Surface* backgroundLoadedSurface=NULL;

    for(int i=0; i<this->rows; i++)
    {
        for(int j=0; j<this->cols; j++)
        {
            if(this->wallsMap[i][j] == '#')
            {
                int num = rand()%8;
                backgroundLoadedSurface=Nivel::Surfaces[num];
            }
            else
            {
                backgroundLoadedSurface=Nivel::Surfaces[8];
            }
            backgroundRect.x = j*Game::objSize;
            backgroundRect.y = i*Game::objSize;
            backgroundRect.w = Game::objSize;
            backgroundRect.h = Game::objSize;
            SDL_BlitScaled(backgroundLoadedSurface,NULL,backgroundSurface,&backgroundRect);
        }
    }

    ///Inicializar matriz que contiene los surface de los items
    SDL_Surface* item=SDL_CreateRGBSurface( 0,Game::objSize, Game::objSize, 32, 0, 0, 0, 0 );
    SDL_SetColorKey(item, SDL_TRUE, SDL_MapRGB(item->format, 255, 0, 255));

    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->cols; j++){
            if(this->itemsMap[i][j]!='#'){
                totalItems++;
                if(this->itemsMap[i][j]=='c'){
                    item=Nivel::Surfaces[9]; //PERLA
                }
                else{
                    item=Nivel::Surfaces[10]; //CAGUAMA
                }
                backgroundRect.x = j*Game::objSize;
                backgroundRect.y = i*Game::objSize;
                backgroundRect.w = Game::objSize;
                backgroundRect.h = Game::objSize;
                SDL_BlitScaled(item,NULL,backgroundSurface,&backgroundRect);
            }
        }
    }
    return backgroundSurface;
}

void Nivel::deleteItem(int row,int col)
{
    this->collectedItems[row][col]=true;
}

void Nivel::checkAtItem(Character *c)
{
    SDL_Surface* calle;
    calle=Nivel::Surfaces[8]; ///CALLE
    SDL_Rect calleRect;
    calleRect.w = Game::objSize;
    calleRect.h = Game::objSize;
    int characterX=c->getX()+20;
    int characterY=c->getY()+20;
    int logicX=characterX/Game::objSize;
    int logicY=characterY/Game::objSize;
    if (characterX<=40)logicX=0;
    if (this->getItemsMap()[logicY][logicX]!='#'&& !this->getCollectedItems()[logicY][logicX]){
        if(characterX == logicX*Game::objSize+20 && characterY == logicY*Game::objSize+20){
            calleRect.x = logicX*Game::objSize;
            calleRect.y = logicY*Game::objSize;
            SDL_BlitScaled(calle,NULL,this->getBackgroundSurface(),&calleRect);
            this->deleteItem(logicY,logicX);

            if(this->getItemsMap()[logicY][logicX]=='c'){//CAGUAMAS
                for(int i=0; i<this->getTotalCholos(); i++){
                    if(this->getCholos()[i]->getStatus() == "attack")
                    {
                        this->getCholos()[i]->changeStatus();
                        this->getCholos()[i]->toggleSurface();
                    }
                }
            }
            if(this->getItemsMap()[logicY][logicX]=='v'){//vidas
                if(this->principal->getLives().size()==1)
                    this->principal->addLive("celular");
                if(this->principal->getLives().size()==0)
                    this->principal->addLive("cartera");
                Game::match->drawLives();
            }

            if(this->getItemsMap()[logicY][logicX]=='.'
            || this->getItemsMap()[logicY][logicX]=='+'
            || this->getItemsMap()[logicY][logicX]=='c'){
                this->principal->setScore(this->principal->getScore()+1);
                this->setTotalItems(Game::match->currentLevel->getTotalItems()-1);
                Game::match->drawScore();
            }
        }
        if(this->getTotalItems()==0){
            SDL_Delay(1000);
            this->setCleared(true);
        }
    }
}

bool Nivel::atCross(Character *c)
{
    int characterX=c->getX();
    int characterY=c->getY();
    int logicX=characterX/Game::objSize;
    int logicY=characterY/Game::objSize;

    if(this->getWallsMap()[logicY][logicX]=='+')
    {
        if(characterX==logicX*Game::objSize && characterY == logicY*Game::objSize)
            return true;
    }
    return false;
}

void Nivel::freeNivel()
{
    for(int i=0;i<11;i++)
    {
        SDL_FreeSurface(Nivel::Surfaces[i]);
    }
}











