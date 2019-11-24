
#include "TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* file_name, SDL_Renderer* render)
{
	SDL_Surface* temp_surface = IMG_Load(file_name);
	SDL_Texture* texture =SDL_CreateTextureFromSurface(render, temp_surface);
	SDL_FreeSurface(temp_surface);

	return texture;
}
