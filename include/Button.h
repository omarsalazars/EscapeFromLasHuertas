#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include <SDL2/SDL.h>
#include <string>
#include "Coordinate.h"

using namespace std;

class Button
{
    private:
    SDL_Surface* surface;
    static SDL_Surface*** buttonsSurfaces;
    string status;
    Coordinate position;
    int height,width;
    public:
    static void initButtons();
    static void freeButtons();
    Button();
    Button(int);
    ~Button();
    SDL_Surface* getSurface(){return this->surface;}
    string getStatus(){return this->status;}
    Coordinate getPosition(){return this->position;}
    int getX(){return this->position.getX();}
    int getY(){return this->position.getY();}
    int getWidth(){return this->width;}
    int getHeight(){return this->height;}
    void toggleSurface(int);
};

#endif // BUTTON_H_INCLUDED
