#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Frog.h>
#include <Log.h>

/*
*   Game class
*
*   This class by default handles window and renderer creation/destruction.
*   Intended to be subclassed. Game state methods must be implemented by child class,
*   which will be called in the main game loop.
*
*
*   LoadContent method
*   This method should handle initializing images
*/
class Game {

    private:
	static SDL_Texture* LoadTexture(const char* file_name, SDL_Renderer* render);
    void LoadContent();
    void UnloadContent();
    
    // Add member variables here
    SDL_Window *window;
    SDL_Renderer *renderer;
    int NUM_THREADS;
    int rows;
    bool running;

    Log* (*log_obj)[6];
    SDL_Rect Eground;//Ending ground
    SDL_Rect Sground;//Starting ground
    SDL_Rect dest;
    Frog* frog;
    SDL_Texture* log_text;
    SDL_Texture* frog_text;
    SDL_Texture* jump_text;
    int camera = 0;
    int upCount = 0;

    
    public:
    Game(int NUM_THREADS, int rows, int winWidth = 800, int winHeight = 400);
    void Update(double delta);
    void Draw(double delta);
    bool getStatus();
    ~Game();
};
