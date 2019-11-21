#pragma once
#include <SDL2/SDL.h>

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
    void LoadContent();
    void UnloadContent();
    
    // Add member variables here
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;

    
    public:
    Game(int winWidth = 800, int winHeight = 400);
    void Update(double delta);
    void Draw(double delta);
    bool getStatus();
    ~Game();
};
