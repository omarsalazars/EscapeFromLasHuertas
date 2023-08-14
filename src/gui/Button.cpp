#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../include/Button.h"

Button::Button(){
    this->surface=NULL;
}

Button::Button(int k)
{
    this->surface=Button::buttonsSurfaces[k][0];
}

void Button::initButtons()
{
    Button::buttonsSurfaces=new SDL_Surface**[3];
    string image_preffix = "img/option";
    string image_suffix = ".png";
    for(int i=0;i<3;i++)
    {
        buttonsSurfaces[i]=new SDL_Surface*[2];
        for(int j=0;j<2;j++)
        {
            string image_number = to_string(i);
            string image_number_2 = to_string(j+1);
            string image_name = image_preffix + image_number + image_number_2 + image_suffix;
            buttonsSurfaces[i][j]=IMG_Load(image_name.c_str());
        }
    }
}

void Button::toggleSurface(int k)
{
    if(this->surface==Button::buttonsSurfaces[k][0])
        this->surface=Button::buttonsSurfaces[k][1];
    else
        this->surface=Button::buttonsSurfaces[k][0];
}

void Button::freeButtons()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<2;j++)
            SDL_FreeSurface(Button::buttonsSurfaces[i][j]);
    }
}

Button::~Button()
{
}
