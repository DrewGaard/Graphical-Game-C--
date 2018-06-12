//FileName:		main.cpp
//Programmer:	Dan Cliburn
//Date:			2/4/2013
//Purpose:		This file defines the main function for this simple video game 

#include "videogame.h"

int main(int argc, char *argv[])  //main() must take these parameters when using SDL
{
	Videogame g;

	g.playGame();

	return 0;
}