# CrossyLogs: The Game

## Contributors
+ Nick Bonavia
+ Geordie Jones
+ Warren Riley

## What's this project?
This project is a parallel implementation of a 2D arcade game, where the player attempts to cross a river by way of logs flowing in a dangerous river. The purpose of this project is to research and analyze the performance increase from parallelizing the game.

## How to compile

This project depends on the SDL2 library for window creation, user I/O, and 2D graphics, and OpenMP for the parallel code. You can aquire this using apt on Linux.

```bash
sudo apt install libsdl2-dev
```

Once the dependency is installed change to the CrossyLogs directory and issue make to build, and then run the program

```bash
make
./crossylogs
```