#include "Game.h"
#include "Log.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;


Log* log_obj;
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
    log_obj = new Log(log_text,this->renderer,100,100);
    log_obj->setSpeed(2);
    log_obj->setDirection(1);
    //Frog = new GameObject(frog_text,this.renderer, 100,50);

}
void Game::Update(double delta) {
    // To-do: Get input, update game world
    log_obj->Update(delta);

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
}
void Game::Draw(double delta) {
    // To-do: Draw images to screen
    // Test: draws a purple background
    SDL_SetRenderDrawColor(renderer, 150, 0, 255, 255);
    SDL_RenderClear(renderer);
    log_obj->Render();
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

