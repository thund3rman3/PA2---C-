#ifndef SDLSCREEN_H
#define SDLSCREEN_H

#include "SDLBitmap.hpp"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

class SDLScreen  
{
private:
    SDL_Window *window;
    SDL_Surface *screen;
    size_t SX, SY;      // rozmery okna
    size_t bg;          // barva pozadi okna

public:
    SDLScreen(size_t X, size_t Y, size_t bgcolor = 0);
    ~SDLScreen();

    void init();
    void close();
    void blit(const SDLBitmap &bmp);
    void update();
    void clear();
};
#endif