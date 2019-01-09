#ifndef MATCH_H
#define MATCH_H
#include <SDL2/SDL.h>
#include "Character.h"
#include "Nivel.h"

class Match
{
    private:

    public:
        Match();
        virtual ~Match();
        static SDL_Surface** vidasSurfaces;
        ///GET y set

        ///GET Y SET FIN
        static void drawCharacter(Character*);
        void close();
        Nivel *currentLevel;
        Principal *principal;
        void drawBackground(SDL_Surface*);
        void playLevel(int);
        void drawLives();
        void loadVidas();
        string getName();
        void setScore();
        void drawScore();
};

#endif // MATCH_H
