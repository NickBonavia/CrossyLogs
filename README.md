# CrossyLogs: The Game

## Contributors
+ [Nick Bonavia](https://github.com/NickBonavia)
+ [Geordie Jones](https://github.com/geoRunstar)
+ [Warren Riley](https://github.com/warrenriley98)

## What's this project?
This project is a parallel implementation of a 2D arcade game, where the player attempts to cross a dangerous river by way of floating logs. The purpose of this project is to research and analyze the performance increase from parallelizing the game.

## How to compile

This project depends on the SDL2 library for window creation, user I/O, and 2D graphics, SDL_image for loading in png files, and OpenMP for the parallel code. You can aquire those libraries by using apt on Linux.

```bash
sudo apt install libsdl2-dev libsdl2-image-dev
```

Once the dependencies are installed change to the CrossyLogs directory and issue make to build, and then run the program

```bash
make
./crossylogs
```
