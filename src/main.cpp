/*
*   
*
*
*
*/

#include "Game.h"
#include <SDL2/SDL.h>
#include <omp.h>
#include <cstdio>

int main(int argc, char* argv[]) {

    Game crossyLogs = Game();
	
    while (crossyLogs.getStatus() == true) {
        
        Uint32 start = SDL_GetTicks();
        crossyLogs.Update(1.0);
        crossyLogs.Draw(1.0);
        Uint32 delta = SDL_GetTicks() - start;

        // Delay based on time to process frame
        /*if (delta < 16) {
            printf("Sleeping %ums\n", 16u - delta);
            SDL_Delay(16u - delta);
        }*/
    }

    return 0;
}
