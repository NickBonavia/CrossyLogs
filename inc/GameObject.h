#pragma once
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
		
		GameObject(SDL_Texture* obj_text, SDL_Renderer* render,SDL_Rect dest)
		{
			renderer = render; 
			object_texture = obj_text;
			destination_rect = dest;
			x_position = destination_rect.x; 
			y_position = destination_rect.y;
		}
protected:
		SDL_Renderer* renderer;
		SDL_Texture* object_texture;
};
