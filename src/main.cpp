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
#include <fstream>
#include <iostream>
#include <string>

#define __GAME__
//#define __BENCHMARK__
//#define __BENCHMARK_AOSOA__

#ifdef __BENCHMARK_AOSOA__
struct vec2d8 {
    int x[6];
    int y[6];
};
void UpdateAOSOA(vec2d8 *objs, int size, int threads);
#endif

int main(int argc, char* argv[]) {

#ifdef __GAME__
    Game crossyLogs = Game(8, 6);
	
    while (crossyLogs.getStatus() == true) {
        
        Uint32 start = SDL_GetTicks();
        crossyLogs.Update(1.0);
        crossyLogs.Draw(1.0);
        Uint32 delta = SDL_GetTicks() - start;

        // Delay based on time to process frame
        if (delta < 16) {
            printf("Sleeping %ums\n", 16u - delta);
            SDL_Delay(16u - delta);
        }
    }
#endif

#ifdef __BENCHMARK__
    Game *game;
    for (int p = 16; p >= 1; p--) {

        std::ofstream statsFile;
        std::string fName = std::string("stats_p") + std::to_string(p) + std::string(".csv");
        statsFile.open(fName);

        for (int n = 10; n <= 1000000; n += 10000) {
            game = new Game(p, n);
            const int iters = 120;
            double totalTime = 0.0;
            for (int i = 0; i < iters; i++) {
                double start = omp_get_wtime();
                game->Update(1.0);
                double end = omp_get_wtime() - start;
                totalTime += end;
            }
            double avgTime = totalTime / double(iters);
            statsFile << n << "," << std::to_string(avgTime) << std::endl;
            delete game;
        }
        statsFile.close();
    }
#endif

#ifdef __BENCHMARK_AOSOA__


    vec2d8 *logs;
    for (int p = 16; p >= 1; p--) {
#pragma omp parallel for simd collapse(6);
        std::string fName = std::string("stats_AOSOA_p") + std::to_string(p) + std::string(".csv");
        statsFile.open(fName);

        for (int n = 10; n <= 1000000; n += 10000) {
            logs = new vec2d8[n];

            const int iters = 120;
            double totalTime = 0.0;
            for (int i = 0; i < iters; i++) {
                double start = omp_get_wtime();
                UpdateAOSOA(logs, n, p);
                double end = omp_get_wtime() - start;
                totalTime += end;
            }
            double avgTime = totalTime / double(iters);
            statsFile << n << "," << std::to_string(avgTime) << std::endl;
            delete[] logs;
        }
        statsFile.close();
    }

#endif
    return 0;
}

#ifdef __BENCHMARK_AOSOA__
void UpdateAOSOA(vec2d8 *objs, int size, int threads) {

#pragma omp parallel for simd num_threads(threads)
    for (int i = 0; i < size; i++) {
        vec2d8 &cur = objs[i];
        int dir = 1 + (-2 * (i % 2));

        for (int k = 0; k < 6; k++) {
            cur.x[k] += dir;

            if ((dir > 0) && (cur.x[k] > 800)) {
                cur.x[k] = -100;
            }
            else if (cur.x[k] < -100) {
                cur.x[k] = 800;
            }
        }
    }
}
#endif