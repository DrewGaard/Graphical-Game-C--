//FileName:		location.cpp
//Programmer:	Dan Cliburn
//Date:			9/11/2015
//Purpose:		This file defines the methods for the location class

#include "location.h"
#include "videoGame.h"

//This method defines how to draw whatever we want to see for objects of this class
void Location::render()
{
	if (visited == true && symbol != ' ') //We have been to this spot and it is not a default location
	{
		//We are using the "symbol" as the texture ID.  Since 
		//"symbol" is a char, it must be casted to an int
		Videogame::renderBitMap((int)(symbol));
	}
}

void Location::takeFromGround(Player& p)	//Ask the user if they want to pick an item up off the ground.
{
	if (ground.getFirstElement() > 0)
	{
		char answer = ' ';
		string item = " ";

		string groundStuff;
		int totalItems;
		totalItems = getGroundItems(groundStuff); //Method for project 8
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Items at Location", groundStuff.c_str(), NULL);
		if (totalItems > 0)	//Add the code to see if the user wants to drop an item
		{
			Item *item;

			const SDL_MessageBoxButtonData buttons[2] = {
					{ 0, 1, "Yes" }, //button with ID 1
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "No" } //button with ID 0
			}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
			const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, "Location", "Do you want to pickup an item?", SDL_arraysize(buttons), buttons, NULL };
			int answer;
			SDL_ShowMessageBox(&messageboxdata, &answer);
			if (answer == 1)	//If the user wants to drop an item in there inventory
			{
				const int MAX_INVENTORY_SIZE = 7;							//Make this the max number of items the user will be able to pickup in the game plus one, becasue of the cancel option
				SDL_MessageBoxButtonData buttonData[MAX_INVENTORY_SIZE];
				char buttonNames[MAX_INVENTORY_SIZE][20];
				for (int i = totalItems; i > 0; i--)
				{
					buttonData[i].flags = 0;
					buttonData[i].buttonid = i;
					item = getGroundItem(i - 1);
					if (item != 0)
					{
						strcpy_s(buttonNames[i], item->getName().c_str());
						buttonData[i].text = buttonNames[i];
					}
					else
					{
						buttonData[i].text = "OOPS";
					}
				}
				buttonData[0].flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
				buttonData[0].buttonid = 0;
				buttonData[0].text = "CANCEL";

				//Show the message box to the user
				const SDL_MessageBoxData messageboxdata2 = { SDL_MESSAGEBOX_INFORMATION, NULL, "Inventory", "Click on the item that you wish to pickup.", totalItems + 1, buttonData, NULL };
				SDL_ShowMessageBox(&messageboxdata2, &answer);	//Answer holds the id of the pressed buttton

				if (answer != 0) //If the user pressed 0 then they must have pressed the cancel button
				{
					item = getGroundItem(answer - 1);
					if (item != 0)
					{
						item = dropItem(item->getName());
						if (item != 0)
						{
							p.pickUpItem(item);
							//world[playerRow][playerCol]->putItemOnGround(item); //Insert the item into the ground list
						}
					}
				}
			}
		}
		//-----------------------------------------------------------------------------------------------------------------------------------WORKING...
		/*
		cout << "The items at this location are..." << endl;
		displayGround(); //ground.print() - Dont use here
		cout << "Would you like to pick up an item? Press 'y' for yes or 'n' for no." << endl;
		cin >> answer;



		if (answer == 'y')
		{
			if (ground.getFirstElement() != 0)
			{
				cout << "What do you want to pick up?" << endl;
				cin >> item;

				Item *nItem = new Item(item);
				p.pickUpItem(nItem);

				Item *i;

				i = ground.remove(item);

				if (i == 0)
				{
					cout << "The item you entered does not exist." << endl;
				}
				else
				{
					return i;
				}
			}
		}
		*/
	}
}

void Location::displayGround()
{
	Item *current = ground.getFirstElement();

	//cout << current << endl; //For testing

	if (current != 0)	//Items in the inventory
	{
		while (current != 0)
		{
			cout << current->getName() << endl;
			current = current->getNext();
		}
	}
	else
	{
		//cout << "No items at this location" << endl;	//This else case should never happen since the function is only called in the takeFromGround() function that checks if an item is in the ground location first
	}
}

int Location::getGroundItems(string &items)
{
	items = "";
	Item *current = ground.getFirstElement();
	int total = 0;

	while (current != 0)
	{
		items += current->getName() + "\n"; //Concatenate the name of the item onto items
		current = current->getNext();
		total++;
	}
	if (total == 0)	//No items in the inventory, displays nothing
	{
		items = "nothing";
	}

	return total;
}