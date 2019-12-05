#pragma once
#include "GameObject.h"

class Frog : public GameObject {
private:
    int jump_dist;
	SDL_Rect orginal;

public:
	SDL_Rect *on_log = nullptr;

    Frog(SDL_Texture *tex, SDL_Renderer *rend, SDL_Rect dest, int jump_dist) : GameObject(tex, rend, dest) {
        
        this->jump_dist = jump_dist;
        destination_rect.w = 32;
        destination_rect.h = 32;
		orginal = dest;
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
        
        if (on_log != nullptr) {
            x_position = on_log->x;
			destination_rect.x = x_position;
        }
    }

    void Move(int direction) {

        y_position += jump_dist * direction;
        destination_rect.y = y_position;
    }

    bool Collision(SDL_Rect *log_rect) {
        if (SDL_HasIntersection(&this->destination_rect, log_rect)) {
            on_log = log_rect;
            return true;
        }
        return false;
    }

	~Frog(){};
};
