#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texture_sheet, SDL_Renderer* render, int x, int y)
{
	renderer = render;
	object_texture = TextureManager::LoadTexture(texture_sheet,render);

	x_position = x;
	y_position =y;
}

void GameObject::Update()
{

	source_rect.h =64;
	source_rect.w =64;
	source_rect.x =0;
	source_rect.y =0;

	destination_rect.x = x_position;
	destination_rect.y = y_position;

	destination_rect.w = source_rect.w;

	destination_rect.h = source_rect.h;

}

void GameObject::Render()
{
	SDL_RenderCopy(renderer,object_texture, &source_rect, &destination_rect);
	
}

