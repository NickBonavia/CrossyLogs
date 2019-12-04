	#include "Game.h"

class GameObject{


	public:
		int x_position;
		int y_position;
		SDL_Rect destination_rect;

		virtual	~GameObject(){};
		virtual void Update(double delta)=0;
		void Render()
		{			
			SDL_RenderCopy(renderer,object_texture, nullptr, &destination_rect);
		}
		
		GameObject(SDL_Texture* obj_text, SDL_Renderer* render, int x, int y)
		{
			renderer = render; 
			object_texture = obj_text;
			x_position = x; 
			y_position = y;
			destination_rect.x = x;
			destination_rect.y = y;			
			destination_rect.w = 64;
			destination_rect.h = 64;
		}
protected:
		SDL_Renderer* renderer;
		SDL_Texture* object_texture;
};
