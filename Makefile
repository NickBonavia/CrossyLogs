
CC = g++
ARGS = -std=c++14
LIBS = -fopenmp -lSDL2 -lSDL2_image
INCLUDES = -I./inc/
SRC = ./src/
EXE = crossylogs

## add files that need to be compiled 
FILES = main.cpp

all:
		$(CC) $(ARGS) $(INCLUDES) $(SRC)*.cpp $(LIBS) -o $(EXE)

clean:
	/bin/rm $(EXE)