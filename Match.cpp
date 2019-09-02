#include "Match.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Game.h"
#include <sstream>
#include <fstream>

Match::Match()
{
    principal=new Principal;
    Match::vidasSurfaces=new SDL_Surface*[2];
    string route="images/vectorizados/",file;
    file=route+"cartera.png";
    Match::vidasSurfaces[0]=IMG_Load(file.c_str());
    if(!Match::vidasSurfaces[0])
        printf("%s",file.c_str());
    file=route+"celular.png";
    Match::vidasSurfaces[1]=IMG_Load(file.c_str());
    if(!Match::vidasSurfaces[1])
        printf("%s",file.c_str());
}

void Match::loadVidas()
{
}

Match::~Match()
{
    for(int i=0;i<2;i++)
    {
        if(Match::vidasSurfaces[i])
        {
            SDL_FreeSurface(Match::vidasSurfaces[i]);
        }
    }
}

void Match::drawLives(){
    SDL_Surface* vida;
    int i=0;
    if(this->principal->getLives().size()==2)
    {
        vida=Match::vidasSurfaces[0];
        Game::drawStretchSurface(vida,900+i*Game::objSize,0,Game::objSize,Game::objSize);
        i++;
        vida=Match::vidasSurfaces[1];
        Game::drawStretchSurface(vida,900+i*Game::objSize,0,Game::objSize,Game::objSize);
    }
    if(this->principal->getLives().size()==1)
    {
        vida=Match::vidasSurfaces[0];
        Game::drawStretchSurface(vida,900+i*Game::objSize,0,Game::objSize,Game::objSize);
        i++;
        vida=SDL_CreateRGBSurface(0,Game::objSize,Game::objSize,32,0,0,0,0);
        Game::drawStretchSurface(vida,900+i*Game::objSize,0,Game::objSize,Game::objSize);
        SDL_FreeSurface(vida);
    }
    if(this->principal->getLives().size()==0)
    {
        vida=SDL_CreateRGBSurface(0,Game::objSize,Game::objSize,32,0,0,0,0);
        Game::drawStretchSurface(vida,900+i*Game::objSize,0,Game::objSize,Game::objSize);
        SDL_FreeSurface(vida);
    }
}

void Match::drawCharacter(Character* character){
    Game::drawStretchSurface(
        character->getSurface(),
        character->getPosition().getX(),
        character->getPosition().getY(),
        Game::objSize,
        Game::objSize
        );
}

void Match::drawBackground(SDL_Surface* backgroundSurface){
    Game::drawStretchSurface(backgroundSurface,0,0,Game::GAME_SCREEN_WIDTH, Game::SCREEN_HEIGHT);
}

void Match::playLevel(int level)
{
    stringstream ss;
    ss << level;
    string numstring = ss.str();

    string nivel="Nivel "+numstring;
    Game::clearWindowSurface();
    Game::drawText(Game::windowSurface,nivel.c_str(),100,350,250,255,255,255,0,0,0);
    Game::updateWindow();
    SDL_Delay(1000);
    Game::clearWindowSurface();
    Game::updateWindow();

    Game::drawText(Game::windowSurface, "NIVEL "+numstring, 30,770,50,255,255,255,0,0,0);
    Game::drawText(Game::windowSurface, "Puntuacion:", 30,770,100,255,255,255,0,0,0);
    Game::match->currentLevel = new Nivel(numstring);

    int totalCholos = Game::match->currentLevel->getTotalCholos();
    Cholo **cholos;
    Principal *principal;
    principal = Game::match->principal;

    cholos = new Cholo*[totalCholos];
    cholos = Game::match->currentLevel->getCholos();

    char newDirection;
    Game::match->drawBackground(Game::match->currentLevel->getBackgroundSurface());
        for(int i=0; i<Game::match->currentLevel->getTotalCholos(); i++){
            Game::match->drawCharacter(cholos[i]);

        }

        Game::match->drawCharacter(Game::match->principal);
        Game::match->drawLives();

        Game::updateWindow();


    SDL_Delay(2000);


    while(!Game::match->currentLevel->getCleared() && !Game::quit && !principal->getLost()){ ///El 1 es not level cleared
        //match.clearWindowSurface();
        SDL_Delay(2);

        ///ACTUALIZAR POSICIONES Y DIRECCIONES PRINCIPAL
        while( SDL_PollEvent(Game::event) != 0)
        {
            if(Game::event->type == SDL_QUIT){Game::quit=true;}
            if(Game::event->type == SDL_KEYDOWN){

                    switch(Game::event->key.keysym.sym)
                    {
                        case SDLK_UP:
                            newDirection='u';
                            break;
                        case SDLK_DOWN:
                            newDirection='d';//down
                            break;
                        case SDLK_LEFT:
                            newDirection = 'l';
                            break;
                        case SDLK_RIGHT:
                            newDirection = 'r';
                            break;
                    }
                    if(principal->canMoveInThatDirection(newDirection)){
                        principal->changeDirection();
                    }
            }
        }
        if(Game::match->currentLevel->atCross(principal) && principal->canMoveInThatDirection(newDirection)){
            principal->setDirection(newDirection);
        }///FIN ACTUALIZAR POSICION Y DIRECCION PRINCIPAL

        ///ACTUALIZAR POSICIONES Y DIRECCIONES CHOLOS
        for(int i=0; i<totalCholos; i++)
        {
            if(cholos[i]->getStatus()=="attack")
            cholos[i]->changeTarget();
            if(Game::match->currentLevel->atCross(cholos[i]))
                cholos[i]->changeDirection();
        }
        ///FIN ACTUALIZAR POSICIONES Y DIRECCIONES

        Game::match->currentLevel->checkAtItem(principal);

        ///CHECAR COLISIONES
        int characterLogicX = (principal->getX()+Game::objSize/2)/Game::objSize;
        int characterLogicY = (principal->getY()+Game::objSize/2)/Game::objSize;
        int choloLogicX;
        int choloLogicY;
        for(int i=0; i<totalCholos; i++)
        {
            choloLogicX = (cholos[i]->getX()+Game::objSize/2)/Game::objSize;
            choloLogicY = (cholos[i]->getY()+Game::objSize/2)/Game::objSize;
            if(characterLogicX==choloLogicX && characterLogicY==choloLogicY)
            {
                if(cholos[i]->getStatus()=="attack")
                {
                    principal->setPosition(principal->getStartingPosition());
                    for(int i=0; i<totalCholos; i++)
                    cholos[i]->setPosition(cholos[i]->getStartingPosition());
                    SDL_Delay(2000);
                    principal->respawn();
                    Game::match->drawLives();
                }
                else
                {
                    cholos[i]->setPosition(cholos[i]->getStartingPosition());
                    principal->setScore(principal->getScore()+5);
                    Game::match->drawScore();
                }

            }
        }
        ///FIN CHECAR COLISIONES
        ///MOTION
        principal->Motion();
        for(int i=0; i<totalCholos; i++){
            cholos[i]->Motion();
        }
        ///FIN MOTION
        ///DIBUJAR
        Game::match->drawBackground(Game::match->currentLevel->getBackgroundSurface());
        for(int i=0; i<Game::match->currentLevel->getTotalCholos(); i++){
            Match::drawCharacter(cholos[i]);
        }
        Game::match->drawCharacter(principal);
        ///FIN DIBUJAR

        Game::updateWindow();
    }
}


string Match::getName()
{
    bool finished = false;
    string nombre="";
    Game::drawText(Game::windowSurface, "Introduce tu nombre", 30,0,0,255,255,255,0,0,0);
    Game::drawText(Game::windowSurface, nombre, 30,0,40,255,255,255,0,0,0);
    Game::updateWindow();


    while(!finished)
    {
        while(SDL_PollEvent(Game::event))
        {
            if(Game::event->type==SDL_QUIT){Game::quit=true;finished=true;}
            if(Game::event->type==SDL_KEYDOWN)
            {
                switch(Game::event->key.keysym.sym)
                {
                    case SDLK_a:
                        nombre+='A';
                    break;
                    case SDLK_b:
                        nombre+='B';
                    break;
                    case SDLK_c:
                        nombre+='C';
                    break;
                    case SDLK_d:
                        nombre+='D';
                    break;
                    case SDLK_e:
                        nombre+='E';
                    break;
                    case SDLK_f:
                        nombre+='F';
                    break;
                    case SDLK_g:
                        nombre+='G';
                    break;
                    case SDLK_h:
                        nombre+='H';
                    break;
                    case SDLK_i:
                        nombre+='I';
                    break;
                    case SDLK_j:
                        nombre+='J';
                    break;
                    case SDLK_k:
                        nombre+='K';
                    break;
                    case SDLK_l:
                        nombre+='L';
                    break;
                    case SDLK_m:
                        nombre+='M';
                    break;
                    case SDLK_n:
                        nombre+='N';
                    break;
                    case SDLK_o:
                        nombre+='O';
                    break;
                    case SDLK_p:
                        nombre+='P';
                    break;
                    case SDLK_q:
                        nombre+='Q';
                    break;
                    case SDLK_r:
                        nombre+='R';
                    break;
                    case SDLK_s:
                        nombre+='S';
                    break;
                    case SDLK_t:
                        nombre+='T';
                    break;
                    case SDLK_u:
                        nombre+='U';
                    break;
                    case SDLK_v:
                        nombre+='V';
                    break;
                    case SDLK_w:
                        nombre+='W';
                    break;
                    case SDLK_x:
                        nombre+='X';
                    break;
                    case SDLK_y:
                        nombre+='Y';
                    break;
                    case SDLK_z:
                        nombre+='Z';
                    break;
                    case SDLK_BACKSPACE:
                        if(nombre.length()>0){
                            Game::clearWindowSurface();
                            string nomAux="";
                            for(int i=0; i<nombre.length()-1; i++){
                                nomAux+=nombre[i];
                            }

                            if(nomAux.length()>=0){
                                nombre=nomAux;
                            }

                        }
                    break;
                    case SDLK_RETURN:
                        finished=true;
                    break;
                }
            }
            Game::drawText(Game::windowSurface, "Introduce tu nombre", 30,0,0,255,255,255,0,0,0);
            Game::drawText(Game::windowSurface, nombre, 30,0,40,255,255,255,0,0,0);
            Game::updateWindow();
        }
    }
    return nombre;
}

void Match::setScore()
{
    fstream file;
    file.open("scores.txt", ios::in);
    fstream auxFile;
    auxFile.open("aux.txt", ios::out);

    time_t now = time(0);
    char* dt = ctime(&now);

    string name = getName();
    int score = Game::match->principal->getScore();

    int fScore;
    string fName, fWDay, fHour, fYear, fNDay, fMonth;
    bool imprimi=false;

    while (file >> fName>>fScore>>fWDay>>fMonth>>fNDay>>fHour>>fYear) {

        if(fScore>score){
            auxFile<<fName<<" "<<fScore<<" "<<fWDay<<" "<<fMonth<<" "<<" "<<fNDay<<" "<<fHour<<" "<<fYear<<endl;
        }
        else
        {
            if(!imprimi){
            auxFile<<name<<" "<<score<<" "<<dt;}
            auxFile<<fName<<" "<<fScore<<" "<<fWDay<<" "<<" "<<fMonth<<" "<<fNDay<<" "<<fHour<<" "<<fYear<<endl;
            imprimi = true;

        }
    }
    if(!imprimi)
    auxFile<<name<<" "<<score<<" "<<dt;


    file.close();
    auxFile.close();
    remove("scores.txt");
    rename("aux.txt", "scores.txt");
    Game::clearWindowSurface();
    Game::drawText(Game::windowSurface, "Se ha registrado tu puntuacion", 30,0,0,255,255,255,0,0,0);
    Game::updateWindow();
    SDL_Delay(1500);
    Game::clearWindowSurface();
}

void Match::drawScore()
{
    stringstream ss;
    ss<<this->principal->getScore();
    string numstring=ss.str();
    Game::drawText(Game::windowSurface, numstring, 30,940,100,255,255,255,0,0,0);
}
