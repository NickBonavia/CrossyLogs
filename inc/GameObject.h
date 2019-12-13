#pragma once
#include "Game.h"

class GameObject{


	public:
		int x_position;
		int y_position;
		SDL_Rect destination_rect;

		virtual	~GameObject(){};
		virtual void Update(double delta) = 0;
		void Render(int cameraY)
		{			
			SDL_Rect tmp = destination_rect;
			tmp.y = tmp.y - cameraY;
			SDL_RenderCopy(renderer,object_texture, nullptr, &tmp);
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
