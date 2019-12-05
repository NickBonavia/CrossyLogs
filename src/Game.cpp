#include "Game.h"
#include "Log.h"
#include "Frog.h"
#include <iostream>
#include <string>
#include <omp.h>
using std::cout;
using std::endl;

//#define __PARALLEL__

Log* log_obj[5][5];
SDL_Rect Eground;//Ending ground
SDL_Rect Sground;//Starting ground
SDL_Rect dest;
//SDL_Texture* frog_text;
SDL_Texture* log_text;


SDL_Texture* Game::LoadTexture(const char* file_name, SDL_Renderer* render)
{
	SDL_Surface* temp_surface = IMG_Load(file_name);
	SDL_Texture* texture =SDL_CreateTextureFromSurface(render, temp_surface);
	SDL_FreeSurface(temp_surface);

	return texture;
}

void Game::LoadContent() {
    // To-do: Load content for game
  
    log_text = LoadTexture("assets/log.png",this->renderer);

    //frog_text = this->LoadTexture("assets/HornFrog.png",this.renderer);
	for(int i = 0;i<5; i++){
		for(int j =0; j<5;j++){
			dest.x=(j*64)+(i*64)+(j*80);
			int d;
			dest.y = (i * 64)+55;
			if(i%2==0){
				d = 1;
			}
			else{
				d= -1;
			}
	dest.w =64;
	dest.h =64;
    	log_obj[i][j] = new Log(log_text,this->renderer,dest);
    	log_obj[i][j]->setSpeed(1);
  		log_obj[i][j]->setDirection(d);
		}
	}

	//Loading the ground objects and their postions
	Sground.x = 0;
	Sground.y = 350;
	Sground.w = 800;
	Sground.h = 50;

	Eground.x = 0;
	Eground.y = 0;
	Eground.w = 800;
	Eground.h = 50;
    //Frog = new GameObject(frog_text,this.renderer, 100,50);

}
void Game::Update(double delta) {
    // To-do: Get input, update game world
	for(int i =0;i<5;i++){
		for(int j =0; j<5;j++){
	    	log_obj[i][j]->Update(delta);
		}
	}
    SDL_Event event;

    // get events
    while (SDL_PollEvent(&event) != 0) {

        // Check what event we received
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
        }
    }
#ifdef __PARALLEL__
#pragma omp parallel for num_threads(4) collapse(2)
#endif
	for(int i =0;i<4;i++){
		for(int j =0; j<4;j++){
	    	log_obj[i][j]->Update(delta);
            cout << omp_get_thread_num() << endl;
		}
	}
}
void Game::Draw(double delta) {
    // To-do: Draw images to screen
    // Test: draws a purple background

	SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	SDL_RenderFillRect(renderer, &Sground);
	SDL_RenderFillRect(renderer, &Eground);
    
	for(int i =0;i<5;i++){
		for(int j =0;j<5;j++){
    		log_obj[i][j]->Render();
		}
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 205, 0);
    SDL_RenderPresent(renderer);
}
void Game::UnloadContent() {
    // To-do: Unload images and free memory
}

/*
*   Get the status of initialization.
*/
bool Game::getStatus() {
    return running;
}

/*
*   Game Constructor
*
*   This method handles initializing SDL2, and window/renderer creation
*/
Game::Game(int winWidth, int winHeight) {

    running = true;

    // Initialize video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL2: Initialization failed - Error " << SDL_GetError() << endl;
        running = false;
    }
    else {
        // Create a window and check its status
        window = SDL_CreateWindow("CrossyLogs", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN);

        if (window == nullptr) {
            cout << "SDL2: Failed to create window - Error " << SDL_GetError() << endl;
            running = false;
        }
        else {
            // Create a renderer and check its status
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer == nullptr) {
                cout << "SDL2: Failed to create renderer - Error " << SDL_GetError() << endl;
                running = false;
            }
            else {
                // Everything was successfull, so load content
                this->LoadContent();
            }
        }
    }
}

/*
*   Game destructor
*
*   This method calls the unload function, and handles
*   SDL2 cleanup.
*/
Game::~Game() {

    this->UnloadContent();

    if (renderer != nullptr)
        SDL_DestroyRenderer(renderer);
    if (window != nullptr)
        SDL_DestroyWindow(window);
    SDL_Quit();
}