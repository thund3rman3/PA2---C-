#ifndef SDLBITMAP_H
#define SDLBITMAP_H

#include <string>
#include <SDL2/SDL.h>
	
class SDLBitmap  
{
private:
    SDL_Surface *bmp;

public:
    int x, y;

    SDLBitmap();
    ~SDLBitmap();
    void clear();
    void loadBMP(const std::string &filename);
    SDL_Surface *getSurface() const;
};
#endif