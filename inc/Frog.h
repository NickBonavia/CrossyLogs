#pragma once
#include "GameObject.h"

class Frog : public GameObject {
private:
    int jump_dist;
	int direction;
	SDL_Rect orginal;
	SDL_Texture *jump_tex, *tex;
	
public:
	SDL_Rect *on_log = nullptr;
	int jump =64;
	int offset = 16;

    Frog(SDL_Texture *tex, SDL_Renderer *rend, SDL_Rect dest, int jump_dist, 		SDL_Texture *jump_tex) : GameObject(tex, rend, dest) {
        
        this->jump_dist = jump_dist;
        destination_rect.w = 32;
        destination_rect.h = 32;
		orginal = dest;
		this->jump_tex = jump_tex;
		this->tex = tex;
    }

	void Reset(){
		on_log = nullptr;
		destination_rect = orginal;
		x_position = destination_rect.x;
		y_position = destination_rect.y;
		destination_rect.w = 32;
        destination_rect.h = 32;
	}

    void Update(double delta) {
        if(jump != 64){
	jump +=4;
	y_position += (4 * direction);
	destination_rect.y = y_position;
	} 
	else 
	{
		this->object_texture = tex;
		if (on_log != nullptr) 
		{
            		x_position = on_log->x;
			destination_rect.x = x_position;
        	}
	}
    }

    void Move(int direct) {
	if(jump ==64){
	this->object_texture = jump_tex;
	jump =0;
	direction = direct;
}
       // y_position += jump_dist * direction;
        //destination_rect.y = y_position;
    }

    bool Collision(SDL_Rect *log_rect) {
        if (SDL_HasIntersection(&this->destination_rect, log_rect)) {
	#pragma omp critical
            on_log = log_rect;
	on_log->x += 16;
            return true;
        }
        return false;
    }

	~Frog(){};
};
