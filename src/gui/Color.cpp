#include <SDL2/SDL.h>

class Color{
    static const SDL_Color WHITE;
    static const SDL_Color BLACK;
};

const SDL_Color Color::WHITE = { (Uint8)255, (Uint8)255, (Uint8)255};
const SDL_Color Color::BLACK = { (Uint8)0, (Uint8)0, (Uint8)0 };