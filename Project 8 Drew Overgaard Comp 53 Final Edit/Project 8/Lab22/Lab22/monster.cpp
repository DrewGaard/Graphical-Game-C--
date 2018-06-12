//Project 8
//Drew Overgaard
//12/3/15

#include "Monster.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <vector>
#include <map>
#include "videoGame.h"
#include <SDL.h> 
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

Monster::Monster(char s)
	: Location(s)
{
	taken = false;
}

void Monster::setTaken(bool t)
{
	taken = t;
}

bool Monster::getTaken()
{
	return taken;
}

void Monster::draw()
{
	if (visited == true && taken == false)
		cout << symbol;
	else if (taken == true)					//If the user takes the crystal we set the location to 's'
		cout << "M";
	else
		cout << ".";
}

int Monster::visit(Player &p)				//Pass in the player object by reference so we know when the player lands on a crystal object
{
	srand(time(NULL));
	int die;
	if (visited == false && taken == false)
	{
		//visited = true;



		//Here we call the SDL_ShowMessageBox function which allows the programmer to
		//specify his/her own buttons. See: https://wiki.libsdl.org/SDL_ShowMessageBox
		string title0 = "You encountered an alien robot!";
		string message0 = "You must fight the alien robot! Goodluck.";
		//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
		//string buttonNames[2] = {"Take crystal", "Leave crystal"};
		const SDL_MessageBoxButtonData buttons[1] = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "FIGHT" }; //button with ID 0
		//NOTE that the buttons appear in the REVERSE order of how they are specified above
		const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title0.c_str(), message0.c_str(), SDL_arraysize(buttons), buttons, NULL };
		//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
		int answer0;
		SDL_ShowMessageBox(&messageboxdata, &answer0); //answer will hold the ID of the pressed button 
		if (answer0 == 0) //The user must have pressed the "Take crystal" button
		{
			do
			{
				die = (rand() % 6) + 1;
				if (die > 4)
				{
					//taken = true;
					PlaySound(TEXT("sounds//punch.wav"), NULL, SND_ASYNC);

					string title = "You defeated the alien robot!";
					string message = "Congratulations! You defeated the alien robot!";
					//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
					//string buttonNames[2] = {"Take crystal", "Leave crystal"};
					const SDL_MessageBoxButtonData buttons[1] = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue" }; //button with ID 0
					//NOTE that the buttons appear in the REVERSE order of how they are specified above
					const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
					//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
					int answer;
					SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button 
					if (answer == 0)
					{
						taken = true;
						p.setGP(3);
					}


					/*
					cout << "Huray! You have defeated the Monster! You may continue on your journey." << endl;
					cout << "You get 5GP!" << endl;
					//p.setGP(5);

					Item *GP = new Item("5GP");
					p.pickUpItem(GP);
					//cout << "You now have a total of " << p.getGP() << "GP!" << endl;
					*/
				}
				else
				{
					string title2 = "You Take Damage!";
					string message2 = "The monster deals 5 damage! Try attaking it again!";
					//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
					//string buttonNames[2] = {"Take crystal", "Leave crystal"};
					const SDL_MessageBoxButtonData buttons[1] = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "FIGHT" }; //button with ID 0
					//NOTE that the buttons appear in the REVERSE order of how they are specified above
					const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title2.c_str(), message2.c_str(), SDL_arraysize(buttons), buttons, NULL };
					//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
					int answer2;
					SDL_ShowMessageBox(&messageboxdata, &answer2); //answer will hold the ID of the pressed button 
					if (answer2 == 0)
					{
						taken = false;
						p.setHP(-5);
						PlaySound(TEXT("sounds//punch.wav"), NULL, SND_ASYNC);
					}
					//cout << "Unfortunatly the monster defeated you. Try again!" << endl;
					//taken = false;
				}
			} while (taken != true);
		}
	}
	/*
	string title = "You defeated the Monster!";
	string message = "Congratulations! You defeated the monster!";
	//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
	//string buttonNames[2] = {"Take crystal", "Leave crystal"};
	const SDL_MessageBoxButtonData buttons[1] = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue" }; //button with ID 0
	//NOTE that the buttons appear in the REVERSE order of how they are specified above
	const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
	//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
	int answer;
	SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button 
	if (answer == 1)
	{
		taken = true;
	}
	*/
	//visited = true;
	return 1;





	/*
		cout << "Oh no! You've come across a Monster! He doesn't look very friendly." << endl;
		cout << "You must battle the Monster in order to survive!" << endl;
		do
		{
			cout << "Press 'r' to roll a die. " << endl;
			cout << "If you roll anything greater than a 2 you defeat the Monster. Good luck. You'll need it." << endl;
			cin >> playerRe;
			if (playerRe == 'r')
			{
				die = (rand() % 6) + 1;
				if (die > 2)
				{
					taken = true;
					cout << "Huray! You have defeated the Monster! You may continue on your journey." << endl;
					cout << "You get 5GP!" << endl;
					//p.setGP(5);

					Item *GP = new Item("5GP");
					p.pickUpItem(GP);
					//cout << "You now have a total of " << p.getGP() << "GP!" << endl;
				}
				else
				{
					cout << "Unfortunatly the monster defeated you. Try again!" << endl;
					taken = false;
				}
			}
		} while (taken != true);
		return 1;
		*/
	}

void Monster::render()
{
	//Only render the picture for this location if we have been here (visited == true)
	//but we did not "Take crystal" (taken == false)
	if (visited == false && taken == false)
	{
			Videogame::renderBitMap((int)(symbol));
	}
}