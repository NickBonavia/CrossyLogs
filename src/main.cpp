/*
*   
*
*
*
*/

#include "Game.h"
#include <SDL2/SDL.h>
#include <omp.h>

int main(int argc, char* argv[]) {

    Game crossyLogs = Game();
    Uint32 delta = SDL_GetTicks();
	
    while (crossyLogs.getStatus() == true) {
        
        delta = SDL_GetTicks() - delta;
        crossyLogs.Update(delta/1000.0);
        crossyLogs.Draw(delta/1000.0);

        // Delay 10ms as not to use 100% CPU
        SDL_Delay(10);
    }

    return 0;
}
