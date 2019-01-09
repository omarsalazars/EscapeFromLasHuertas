#include "Game.h"
#include "Match.h"
#include "Button.h"
#include "Nivel.h"
#include <iostream>
#include <string>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

Game::Game(){
    this->quit=false;
    srand(time(NULL));
}

bool Game::initGame(){

    bool success=true;
    Button::initButtons();
    Nivel::initNivel();
    TTF_Init();

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		Game::window = SDL_CreateWindow( "Escape from Las Huertas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( Game::window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
			Game::windowSurface = SDL_GetWindowSurface( Game::window );
	}
	Game::event=new SDL_Event();
	return success;
}
void Game::drawStretchSurface(SDL_Surface* surface,int x,int y,int w,int h)
{
    SDL_Rect stretchRect;
    stretchRect.x = x;
    stretchRect.y = y;
    stretchRect.w = w;
    stretchRect.h = h;
    SDL_BlitScaled(surface,NULL,Game::windowSurface,&stretchRect);
}

void Game::displayMenu()
{
    Game::clearWindowSurface();
    SDL_Surface* title=IMG_Load("images/vectorizados/title.png");
    drawStretchSurface(title,350,50,400,200);
    Button **buttons;
    buttons=new Button*[3];
    for(int i=0;i<3;i++)
    {
        buttons[i]=new Button(i);
        if(i==0)
            buttons[i]->toggleSurface(i);
        drawStretchSurface(buttons[i]->getSurface(),400,300+(70*i),300,70);
    }
    Game::updateWindow();
    SDL_Event* event = new SDL_Event;
    int option=0;
    bool played=false;
    while(!Game::quit)
    {
        if(played)
        {
            played=false;
            drawStretchSurface(title,350,50,400,200);
            for(int i=0;i<3;i++)
                drawStretchSurface(buttons[i]->getSurface(),400,300+(70*i),300,70);
            Game::updateWindow();
        }
        while(SDL_PollEvent(event)!=0)
        {
            if(event->type==SDL_QUIT){quit=true;}
            if(event->type==SDL_KEYDOWN)
            {
                int aux=option;
                switch(event->key.keysym.sym)
                {
                    case SDLK_UP:
                        if(option>0)
                            option--;
                    break;
                    case SDLK_DOWN:
                        if(option<2)
                            option++;
                    break;
                    case SDLK_RETURN:
                    switch(option)
                    {
                        case 0:
                            this->playMatch();
                            played=true;
                            break;
                        case 1:
                            Game::displayScores();
                            Game::clearWindowSurface();
                            played=true;
                            break;
                        case 2:
                            this->exit();
                            break;
                    }
                    break;
                }
                if(aux!=option)
                {
                    Game::clearWindowSurface();
                    drawStretchSurface(title,350,50,400,200);
                    buttons[aux]->toggleSurface(aux);
                    buttons[option]->toggleSurface(option);
                    for(int i=0;i<3;i++)
                    {
                        drawStretchSurface(buttons[i]->getSurface(),400,300+(70*i),300,70);
                    }
                    Game::updateWindow();
                }
            }
        }
    }
}

void Game::updateWindow(){
    SDL_UpdateWindowSurface(Game::window);
}

void Game::playMatch()
{
        Game::match=new Match();
        for(int i=1;i<=3;i++)
        {
            Game::match->playLevel(i);
            if(Game::quit==true)
            {
               return;
            }
            Game::clearWindowSurface();
            if(Game::match->principal->getLost() || Game::quit)
            {
                Game::clearWindowSurface();
                Game::drawText(Game::windowSurface,"Perdiste :(",100,350,250,255,255,255,0,0,0);
                Game::updateWindow();
                SDL_Delay(1000);
                Game::clearWindowSurface();
                Game::updateWindow();
                Game::match->setScore();
                break;
            }
            delete Game::match->currentLevel;
        }
        if(!Game::match->principal->getLost())
        {
                Game::clearWindowSurface();
                Game::drawText(Game::windowSurface,"Ganaste! :D",100,350,250,255,255,255,0,0,0);
                Game::updateWindow();
                SDL_Delay(1000);
                Game::clearWindowSurface();
                Game::updateWindow();
                Game::match->setScore();
        }

        delete Game::match->principal;
        delete Game::match;
}

void Game::exit()
{
    Game::quit=true;
}

void Game::clearWindowSurface(){
    SDL_FillRect(Game::windowSurface, NULL, 0x000000);
}

void Game::free(){
    Nivel::freeNivel();
    Button::freeButtons();
}

void Game::drawText(SDL_Surface* screen, string str,int size, int x, int y,int fR, int fG, int fB,int bR, int bG, int bB)
{
    TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", size );
    if(!font)
    {
        printf("NEL PERRO\n");
        return;
    }
    SDL_Color foregroundColor = { fR, fG, fB };
    SDL_Color backgroundColor = { bR, bG, bB };
    SDL_Surface* textSurface= TTF_RenderText_Shaded(font, str.c_str(), foregroundColor, backgroundColor);
    SDL_Rect textLocation = { x, y, 0, 0 };
    SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

void Game::displayScores()
{
    Game::clearWindowSurface();
    Game::drawText(Game::windowSurface, "Puntuaciones",20,0, 0, 255,255,255,0,0,0);

    fstream file;
    file.open("scores.txt", ios::in);

    int fScore;
    string info;
    int cont = 1;
    Game::drawText(Game::windowSurface, "Alias   Puntuacion  Fecha",20,20, cont*25, 255,255,255,0,0,0);
    cont++;

    while (getline(file,info)) {
        Game::drawText(Game::windowSurface, info,20,20, cont*25, 255,255,255,0,0,0);
        cont++;
    }
    Game::drawText(Game::windowSurface, "Presiona Enter para continuar",20,0, cont*25, 255,255,255,0,0,0);
    bool salir = false;
    file.close();
    Game::updateWindow();

    while(!salir)
    {
        while(SDL_PollEvent(Game::event))
        {
            if(Game::event->type==SDL_QUIT){Game::quit=true;salir=true;}
            if(Game::event->type==SDL_KEYDOWN)
            {
                switch(Game::event->key.keysym.sym)
                {
                    case SDLK_RETURN:
                        salir = true;
                    break;
                }
            }
        }
    }
    Game::clearWindowSurface();
}
