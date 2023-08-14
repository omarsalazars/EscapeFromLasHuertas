#include <stdio.h>
#include <string>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/Match.h"
#include "../include/Principal.h"
#include "../include/Kevin.h"
#include "../include/Brayan.h"
#include "../include/Character.h"
#include "../include/Nivel.h"
#include "../include/Game.h"
#include "../include/Button.h"

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

int main()
{
    Game game;
    game.initGame();
    while(!Game::quit)
    {
        ///llamar menu
        game.displayMenu();
        ///REGISTRAR PUNTUACION
    }
    game.free();
}



