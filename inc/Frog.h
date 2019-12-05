#pragma once
#include "GameObject.h"

class Frog : public GameObject {
private:
    SDL_Rect *on_log = nullptr;
    int jump_dist;

public:
    Frog(SDL_Texture *tex, SDL_Renderer *rend, SDL_Rect dest, int jump_dist) : GameObject(tex, rend, dest) {
        
        this->jump_dist = jump_dist;
        destination_rect.w = 32;
        destination_rect.h = 32;
    }

    void update(double delta) {
        
        if (on_log != nullptr) {
            x_position = on_log->x;
        }
    }

    void move(int direction) {

        y_position += jump_dist * direction;
        destination_rect.y = y_position;
    }

    bool collision(SDL_Rect *log_rect) {
        if (SDL_HasIntersection(&this->destination_rect, log_rect)) {
            on_log = log_rect;
            return true;
        }
        return false;
    }
};