//Drew Overgaard
//Comp 53
//Project 6

#include "Shop.h"
#include <iostream>
#include <map>
#include <SDL.h> 

Shop::Shop(char s)
	: Location(s)
{
	taken = false;
}

void Shop::setTaken(bool t)
{
	taken = t;
}

bool Shop::getTaken()
{
	return taken;
}

void Shop::draw()
{
	if (visited == true && taken == false)
		cout << symbol;
	else if (taken == true)					//No need for this in the shop class
		cout << "s";
	else
		cout << ".";
}

int Shop::visit(Player &p)				//Pass in the player object by reference so we know when the player lands on a crystal object
{
	//Using map for shop items
	std::map <string, Item> data;

	Item i1, i2, i3;

	i1.setName("Dagger");
	i2.setName("ShortSword");
	i3.setName("LongSword");

	data["Dagger"] = i1;
	data["ShortSword"] = i2;
	data["LongSword"] = i3;


	string title = "Shop";
	string message = "You've come to a Shop. You can use your GP to purchase weapons here. Press 'Enter' to shop or 'Exit' to continue." ;
	//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
	//string buttonNames[2] = {"Take crystal", "Leave crystal"};
	const SDL_MessageBoxButtonData buttons[2] = {
			{ 0, 1, "Shop" }, //button with ID 1
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Exit" } //button with ID 0
	}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
	const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
	//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
	int answer;
	SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button 
	if (answer == 0)
	{
		visited = true;
		taken = false;
		return 1;
	}

	if (answer == 1)
	{
		char playerRe2;
		visited = true;

		string title2 = "Shop";
		string message2 = "'Hello " + p.getName() + ", and welcome to my Shop', the Shopkeeper says with a smile. We have 3 different weapons available. We have a Dagger[2GP], a Short Sword[6GP] and a Long Sword[10GP].";
		//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
		//string buttonNames[2] = {"Take crystal", "Leave crystal"};
		const SDL_MessageBoxButtonData buttons[4] = {
				{ 0, 1, "Dagger" }, //button with ID 1
				{ 0, 2, "Short Sword" }, //button with ID 2
				{ 0, 3, "Long Sword" }, //button with ID 3
				{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Exit" } //button with ID 0
		}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
		const SDL_MessageBoxData messageboxdata2 = { SDL_MESSAGEBOX_INFORMATION, NULL, title2.c_str(), message2.c_str(), SDL_arraysize(buttons), buttons, NULL };
		//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
		int answer2;
		SDL_ShowMessageBox(&messageboxdata2, &answer2); //answer will hold the ID of the pressed button 

		if (answer2 == 1 && p.getGP() >= 2)
		{

			string title3 = "Shop";
			string message3 = "You purchased the Dagger. That's a fine choice! Enjoy!";
			//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
			//string buttonNames[2] = {"Take crystal", "Leave crystal"};
			const SDL_MessageBoxButtonData buttons[1] = {
					//{ 0, 1, "Shop" }, //button with ID 1
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue" } //button with ID 0
			}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
			const SDL_MessageBoxData messageboxdata3 = { SDL_MESSAGEBOX_INFORMATION, NULL, title3.c_str(), message3.c_str(), SDL_arraysize(buttons), buttons, NULL };
			//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
			int answer3;
			SDL_ShowMessageBox(&messageboxdata3, &answer3); //answer will hold the ID of the pressed button
			if (answer3 == 0)
			{
				p.setGP(-2);
				//p.setWeapon("Dagger");
				Item *Weapon = new Item(i1); //Pass in the map 
				p.pickUpItem(Weapon);
				//cout << "Press 'n' to exit the shop. Otherwise, press 'y' to continue browsing." << endl;
				return 1;
			}
		}
		else if (answer2 == 0)
		{
			string title6 = "Shop";
			string message6 = "Come back soon!";
			//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
			//string buttonNames[2] = {"Take crystal", "Leave crystal"};
			const SDL_MessageBoxButtonData buttons[1] = {
					//{ 0, 1, "Shop" }, //button with ID 1
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue" } //button with ID 0
			}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
			const SDL_MessageBoxData messageboxdata6 = { SDL_MESSAGEBOX_INFORMATION, NULL, title6.c_str(), message6.c_str(), SDL_arraysize(buttons), buttons, NULL };
			//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
			int answer6;
			SDL_ShowMessageBox(&messageboxdata6, &answer6); //answer will hold the ID of the pressed button
			if (answer6 == 0)
			{
				return 1;
			}

		}
		else if (answer2 == 2 && p.getGP() >= 6)
		{


			string title4 = "Shop";
			string message4 = "You purchased the Short Sword. That's a great choice! Enjoy!";
			//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
			//string buttonNames[2] = {"Take crystal", "Leave crystal"};
			const SDL_MessageBoxButtonData buttons[1] = {
					//{ 0, 1, "Shop" }, //button with ID 1
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue" } //button with ID 0
			}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
			const SDL_MessageBoxData messageboxdata4 = { SDL_MESSAGEBOX_INFORMATION, NULL, title4.c_str(), message4.c_str(), SDL_arraysize(buttons), buttons, NULL };
			//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
			int answer4;
			SDL_ShowMessageBox(&messageboxdata4, &answer4); //answer will hold the ID of the pressed button
			if (answer4 == 0)
			{
				p.setGP(-6);
				//p.setWeapon("ShortSword");
				Item *Weapon = new Item("ShortSword");
				p.pickUpItem(Weapon);
				return 1;
			}
		}
		else if (answer2 == 3 && p.getGP() >= 10)
		{


			string title5 = "Shop";
			string message5 = "You purchased the Long Sword. That's the best choice! Enjoy!";
			//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
			//string buttonNames[2] = {"Take crystal", "Leave crystal"};
			const SDL_MessageBoxButtonData buttons[1] = {
					//{ 0, 1, "Shop" }, //button with ID 1
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue" } //button with ID 0
			}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
			const SDL_MessageBoxData messageboxdata5 = { SDL_MESSAGEBOX_INFORMATION, NULL, title5.c_str(), message5.c_str(), SDL_arraysize(buttons), buttons, NULL };
			//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
			int answer5;
			SDL_ShowMessageBox(&messageboxdata5, &answer5); //answer will hold the ID of the pressed button
			if (answer5 == 0)
			{
				p.setGP(-10);
				//p.setWeapon("LongSword");
				Item *Weapon = new Item("LongSword");
				p.pickUpItem(Weapon);
				return 1;
			}
		}
		else
		{
			string title6 = "Shop";
			string message6 = "You either don't have enough GP for the item you selected or you entered an invalid option.";
			//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
			//string buttonNames[2] = {"Take crystal", "Leave crystal"};
			const SDL_MessageBoxButtonData buttons[1] = {
					//{ 0, 1, "Shop" }, //button with ID 1
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue" } //button with ID 0
			}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
			const SDL_MessageBoxData messageboxdata6 = { SDL_MESSAGEBOX_INFORMATION, NULL, title6.c_str(), message6.c_str(), SDL_arraysize(buttons), buttons, NULL };
			//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
			int answer6;
			SDL_ShowMessageBox(&messageboxdata6, &answer6); //answer will hold the ID of the pressed button
			if (answer6 == 0)
			{
				return 1;
			}
		}
	}
	
	return 1;
}