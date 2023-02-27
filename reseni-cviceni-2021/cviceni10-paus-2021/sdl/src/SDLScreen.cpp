#include "SDLScreen.hpp"

SDLScreen::SDLScreen(size_t X, size_t Y, size_t bgcolor):window(nullptr), screen(nullptr), SX(X), SY(Y), bg(bgcolor)
{

}

SDLScreen::~SDLScreen()
{

}

void SDLScreen::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::string("Init error!");
    }
    
    window = SDL_CreateWindow("PA2 cviko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SX, SY, SDL_WINDOW_SHOWN);
    if (!window) 
    {
        throw std::string("Window Init Error!");
    }

    screen = SDL_GetWindowSurface(window);
}

void SDLScreen::close()
{
    SDL_DestroyWindow(window);
    SDL_Quit();

    window = nullptr;
}

void SDLScreen::update()
{
    SDL_UpdateWindowSurface(window);
}

void SDLScreen::clear()
{
    SDL_FillRect(screen, NULL, bg);
}

void SDLScreen::blit(const SDLBitmap &bmp)
{
    SDL_Rect r;
    r.x = bmp.x;
    r.y = bmp.y;

    SDL_BlitSurface(bmp.getSurface(), NULL, screen, &r);
}