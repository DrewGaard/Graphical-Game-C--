//Project 8
//Drew Overgaard
//12/3/15

//FileName:		main.cpp
//Programmer:	Dan Cliburn
//Date:			2/4/2013
//Purpose:		This file defines the main function for this simple video game 

/*
I decided to add sound to my game as the one new feature. I used the MSSystem.h header file in order to impliment the sound.
I got the sound effects that I used in the game from the website SoundBible.com.
The sound effects are present during combat, when a punch sound plays when the user clicks fight.
There is a sound played when the user picks an item up from the ground and there is a sound played when the user finds the time portal.

---------------Extra Features---------------
I added both a Health and GP variable to the player class so that the player can collect GP during the game and there HP is affected by combat.
I added a shop location to the game where the user can buty items using GP they collect from fighting alien robots.
I added a simple combat system so the player can fight the alien robots using random number generation.
I added the ability for the player to restart the game if they die during combat.
*/
#include "videogame.h"

int main(int argc, char *argv[])  //main() must take these parameters when using SDL
{
	Videogame g;

	g.playGame();

	return 0;
}