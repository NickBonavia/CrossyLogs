	#include "Game.h"

class GameObject{


	public:
		GameObject(const char* texture_sheet, SDL_Renderer* render, int x, int y);
		~GameObject();

		void Update();
		void Render();


	private:

		SDL_Texture* object_texture;


		int x_position;
		int y_position;

		SDL_Rect source_rect, destination_rect;

		SDL_Renderer* renderer;



};
