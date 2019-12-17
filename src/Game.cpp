#include "Game.h"
#include "Log.h"
#include "Frog.h"
#include <iostream>
#include <string>
#include <omp.h>
#include <cstdio>

using std::cout;
using std::endl;

#define __PARALLEL__
//#define __UPDATE_ONLY__

const int COLS = 6;

SDL_Texture* Game::LoadTexture(const char* file_name, SDL_Renderer* render)
{
	SDL_Surface* temp_surface = IMG_Load(file_name);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, temp_surface);
	SDL_FreeSurface(temp_surface);

	return texture;
}

void Game::LoadContent() {
    // To-do: Load content for game
  
    log_text = LoadTexture("assets/log.png",this->renderer);
	frog_text = LoadTexture("assets/HornFrog.png", this->renderer);
	jump_text = LoadTexture("assets/HornFrogJump.png", this->renderer);

	log_obj = new Log*[this->rows][COLS];

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < COLS; j++){
			
			dest.x = (j*64) + (j*80);
			int d;
			dest.y = 310 - (i * 64);

			if(i % 2 == 0){
				d = 1;
			}
			else{
				d= -1;
			}

			dest.w = 60;
			dest.h = 60;
    		log_obj[i][j] = new Log(log_text, this->renderer, dest);
  			log_obj[i][j]->setDirection(d);
		}
	}

	//Loading the ground objects and their postions
	Sground.x = 0;
	Sground.y = 350;
	Sground.w = 800;
	Sground.h = 50;

	Eground.x = 0;
	Eground.y = 310 - (rows * 64);
	Eground.w = 800;
	Eground.h = 50;

	dest.x = 384;
	dest.y = 385;
	frog = new Frog(frog_text, this->renderer, dest, 64,jump_text);

}
void Game::Update(double delta) {
#ifndef __UPDATE_ONLY__
    // To-do: Get input, update game world
    SDL_Event event;

    // get events
    while (SDL_PollEvent(&event) != 0) {

        // Check what event we received
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_w:
					case SDLK_UP:
						frog->Move(-1);
						if (frog->jump == 0)
							upCount++;
						break;
					case SDLK_s:
					case SDLK_DOWN:
						frog->Move(1);
						if (frog->jump == 0)
							upCount--;
						break;
					default:
						break;
				}
        }
    }
	if ((upCount > 2) && (upCount < (rows - 2)) && (frog->jump != 64) && (frog->direction == -1))
		camera -= 4;
	if ((upCount < (rows - 2)) && (camera != 0) && (frog->jump != 64) && (frog->direction == 1))
		camera += 4;

	bool hit = false;

//#ifdef __PARALLEL__
//#pragma omp parallel for num_threads(NUM_THREADS) collapse(2) reduction(||:huh)
//#endif
	for(int k = 0; k < rows; k++){
		for(int kk = 0; kk < COLS; kk++){
			if(!hit){
				hit = frog->Collision(&log_obj[k][kk]->destination_rect);
			}
		}
	}
	if(!hit && (frog->jump == 64)){
		frog->Reset();
		upCount = 0;
		camera = 0;
	}

	frog->Update(delta);
#endif
	double startUp = omp_get_wtime();
#ifdef __PARALLEL__
#pragma omp parallel for num_threads(NUM_THREADS) collapse(2)
#endif
	for(int i =0;i<rows;i++){
		for(int j =0; j < COLS;j++){
	    	log_obj[i][j]->Update(delta);
		}
	}
	double endUp = omp_get_wtime() - startUp;
}
void Game::Draw(double delta) {
    // To-do: Draw images to screen
    // Test: draws a purple background

	SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	SDL_Rect tmpGround = Sground;
	tmpGround.y -= camera;
	SDL_RenderFillRect(renderer, &tmpGround);
	tmpGround = Eground;
	tmpGround.y -= camera;
	SDL_RenderFillRect(renderer, &tmpGround);
    
	for(int i = 0;i<rows;i++){
		for(int j = 0;j<COLS;j++){
    		log_obj[i][j]->Render(camera);
		}
	}
	frog->Render(camera);
	SDL_SetRenderDrawColor(renderer, 0, 0, 205, 0);
    SDL_RenderPresent(renderer);
}
void Game::UnloadContent() {
    // To-do: Unload images and free memory
	SDL_DestroyTexture(log_text);
	SDL_DestroyTexture(frog_text);
	SDL_DestroyTexture(jump_text);

	for (int i = 0; i < this->rows; i++) {
		for (int k = 0; k < COLS; k++) {
			delete log_obj[i][k];
		}
	}
	delete[] log_obj;

	delete frog;
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
Game::Game(int NUM_THREADS, int rows, int winWidth, int winHeight) {

    running = true;
	this->NUM_THREADS = NUM_THREADS;
	this->rows = rows;

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
