#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "Character.h"
#include <SDL2/SDL.h>
#include <stack>


class Principal : public Character
{
    private:
    stack<string> lives;
    bool lost;
    int score;
    public:
        Principal();
        virtual ~Principal();
        int getScore(){return this->score;}
        void changeDirection();
        stack<string> getLives(){return this->lives;}
        bool getLost(){return this->lost;}
        void setLives(stack<string> vidas){this->lives=lives;}
        void setScore(int score){this->score=score;}
        void respawn();
        Uint32 respawnLifeCallback(Uint32 interval);
        static Uint32 respawnLifeCallback(Uint32 interval,void* param);
        void addLive(string vida){this->lives.push(vida.c_str());}
        void popLive(){this->lives.pop();}
};

#endif // PRINCIPAL_H
