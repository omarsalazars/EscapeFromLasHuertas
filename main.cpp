#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <cstdio>
#include <string>
#include "Match.h"
#include "Principal.h"
#include "Kevin.h"
#include "Brayan.h"
#include "Character.h"
#include "Nivel.h"
#include "Game.h"
#include "Button.h"
#include <fstream>

SDL_Window* Game::window=NULL;
SDL_Surface* Game::windowSurface=NULL;
SDL_Event* Game::event=NULL;
Match* Game::match=NULL;
bool Game::quit=false;
SDL_Surface*** Button::buttonsSurfaces=NULL;
SDL_Surface** Nivel::Surfaces=NULL;
SDL_Renderer* renderer=NULL;
SDL_Texture* texture=NULL;
SDL_Surface** Match::vidasSurfaces=NULL;

int main(int argc, char *argv[])
{
    printf("AAAAAAAAAAA");
    Game game;
    game.initGame();
    while(!Game::quit)
    {
        ///llamar menu
        game.displayMenu();
        ///REGISTRAR PUNTUACION
    }
    game.free();
    return 0;
}



