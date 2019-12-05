#pragma once
#include "GameObject.h"

class Log: public GameObject{
public:
	Log(SDL_Texture* tex, SDL_Renderer* ren, int x, int y): GameObject(tex,ren,x,y){
	
		 renderer=ren; 
		object_texture=tex;
		 x_position=x; 
		 y_position=y;

	destination_rect.w =64;

	destination_rect.h = 64;
	destination_rect.x = x_position;
	destination_rect.y = y_position;
	};
	void Update(double delta){
	x_position += speed * direction;
	

	if(direction > 0){
		if(x_position > 800){
			x_position = -100;
		}
	}else{
		if(x_position < -100){
			x_position = 800;
		}
	}

	destination_rect.x = int(x_position);
	destination_rect.y = y_position;
	}
	double getSpeed(){return speed;}
	int getDirection(){return direction;}
	void setSpeed(double s){speed =s;}
	void setDirection(int d){ direction =d;}
private:
 double speed=1.0;
 int direction=1;
};
