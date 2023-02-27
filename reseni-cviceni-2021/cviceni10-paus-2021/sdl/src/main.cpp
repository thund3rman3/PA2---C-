#include <iostream>
#include "SDLScreen.hpp"
#include "SDLBitmap.hpp"

int main( int argc, char* args[] )
{
	SDLScreen sdl(640,480);
	SDLBitmap bmp;

	try
	{
		sdl.init();
	}
	catch (std::string& e)
	{
		std::cout << e << std::endl;
		return -1;
	}

	try
	{
		bmp.loadBMP("assets/beer.bmp");
	}
	catch (std::string &e)
	{
		std::cout << e << std::endl;
		return -1;
	}

	SDL_Event e;
	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_UP:
					bmp.y -= 10;
					break;

				case SDLK_DOWN:
					bmp.y += 10;
					break;

				case SDLK_LEFT:
					bmp.x -= 10;
					break;

				case SDLK_RIGHT:
					bmp.x += 10;
					break;

				default:
					break;
				}
			}
		}

		sdl.clear();
		sdl.blit(bmp);
		sdl.update();

		SDL_Delay(50);
	}

	sdl.close();
	
	return 0;
}