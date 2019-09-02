#include "Button.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
    char arr[100]="img/option";
    arr[12]='.';
    arr[13]='p';
    arr[14]='n';
    arr[15]='g';
    for(int i=0;i<3;i++)
    {
        buttonsSurfaces[i]=new SDL_Surface*[2];
        for(int j=0;j<2;j++)
        {
            arr[10]=i+'0';
            arr[11]=j+'0'+1;
            buttonsSurfaces[i][j]=IMG_Load(arr);
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
