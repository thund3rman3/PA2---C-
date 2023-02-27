#include "SDLBitmap.hpp"

SDLBitmap::SDLBitmap():bmp(nullptr),x(0),y(0) {}
SDLBitmap::~SDLBitmap() 
{
    clear();
};
void SDLBitmap::loadBMP(const std::string &filename)
{
    bmp = SDL_LoadBMP(filename.c_str());
    if (!bmp)
    {
        throw std::string("Error loading bmp.");
    }
}

void SDLBitmap::clear()
{
    if (bmp)
    {
        SDL_FreeSurface(bmp);
        bmp = nullptr;
    }
}

SDL_Surface* SDLBitmap::getSurface() const
{
    return bmp;
}