#include "CommonFunc.h"

void CommonFunc::logSDLError(std::ostream& os, const std::string& msg, bool fatal)
{
	os << msg << " Error: " << SDL_GetError() << std::endl;
	if (fatal)
	{
		SDL_Quit();
		exit(1);
	}
}

void CommonFunc::logIMGError(std::ostream& os, const std::string& msg, bool fatal)
{
	os << msg << " Error: " << IMG_GetError() << std::endl;
	if (fatal)
	{
		IMG_Quit();
		exit(1);
	}
}

void CommonFunc::logMixError(std::ostream& os, const std::string& msg, bool fatal)
{
	os << msg << " Error: " << Mix_GetError() << std::endl;
	if (fatal)
	{
		Mix_Quit();
		exit(1);
	}
}

void CommonFunc::load_texture(SDL_Renderer* renderer, const std::string& path, SDL_Texture* &texture)
{
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		logIMGError(std::cout, "IMG_Load", true);
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL)
		{
			logSDLError(std::cout, "SDL_CreateTextureFromSurface", true);
		}
		SDL_FreeSurface(loadedSurface);
	}
}