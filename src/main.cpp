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
    double delta = 0.0;

    while (crossyLogs.getStatus() == true) {
        
        delta = omp_get_wtime() - delta;
        crossyLogs.Update(delta);
        crossyLogs.Draw(delta);

        // Delay 10ms as not to use 100% CPU
        SDL_Delay(10);
    }

    return 0;
}