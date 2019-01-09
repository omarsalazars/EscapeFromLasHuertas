#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL2/SDL.h>
#include "Match.h"

class Game
{
    private:
    public:
        static bool quit;
        static int cont;
        static const int objSize = 40;
        static const int SCREEN_WIDTH=1100,SCREEN_HEIGHT=680,GAME_SCREEN_WIDTH=760;
        static void drawStretchSurface(SDL_Surface*,int,int,int,int);
        static void clearWindowSurface();
        static void updateWindow();
        void displayMenu();
        void playMatch();
        void checkScores();
        void exit();
        void free();
        Game();
        virtual ~Game(){}
        ///GET te
        ///GET Y SET FIN
        static SDL_Window *window;
        static SDL_Surface *windowSurface;
        static SDL_Event* event;
        bool initGame();
        static Match *match;
        static void drawText(SDL_Surface*,string,int,int,int,int,int,int,int,int,int);
        static void displayScores();
};

#endif // GAME_H_INCLUDED
