The COMPILE.sh file is available for compiling
it can be run by simpling calling it in cmd

in order to compile seperately use the following:

g++ -std=c++11 -c ./src/Game.cpp ./src/GameBank.cpp ./src/GameState.cpp ./src/SearchService.cpp ./src/FileUtils.cpp ./src/SearchSolution.cpp

g++ -o Game.exe Game.o GameBank.o GameState.o SearchService.o FileUtils.o SearchSolution.o

This assumes that the heirarchy of files is kept the same.
Working Dir: inside the Programming Assignment 1 folder
src: cpp files
headers: header files