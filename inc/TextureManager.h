
#include "Game.h"
#include "SDL2/SDL_image.h"

class TextureManager{


	public: 
		static SDL_Texture* LoadTexture(const char* file_name, SDL_Renderer* render);

};
