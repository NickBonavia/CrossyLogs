	#include "Game.h"

class GameObject{


	public:
		virtual	~GameObject(){};

		virtual void Update(double delta)=0;
		void Render()
		{			
		SDL_RenderCopy(renderer,object_texture, &source_rect, &destination_rect);
		}
	protected:
		
		GameObject(SDL_Texture* obj_text, SDL_Renderer* render, int x, int y)
		{
		 renderer=render; 
		object_texture=obj_text;
		 x_position=x; 
		 y_position=y; }


		void setTexture(SDL_Texture* obj_text){object_texture=obj_text;}
		int getX(){ return x_position;}
		int getY(){ return y_position;}
		void setX(int x){ x_position=x;}
		void setY(int y){ y_position=y;}
		SDL_Rect getSourceRect(){ return source_rect;}
		SDL_Rect getDestinationRect(){ return destination_rect;}

		void setSourceRect(SDL_Rect sr){  source_rect=sr;}
		void setDestinationRect(SDL_Rect dr){ destination_rect=dr;}

		SDL_Rect source_rect, destination_rect;
		SDL_Renderer* renderer;
		SDL_Texture* object_texture;

		int x_position;
		int y_position;



};
