//Project 8
//Drew Overgaard
//12/3/15

//FileName:		player.cpp
//Programmer:	Dan Cliburn
//Date:			9/15/2015
//Purpose:		This file defines the methods for the player class

#include "player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <SDL.h>
#include <Windows.h>
#include <mmsystem.h>
using namespace std;

Player::Player(string n)
{
	name = n;
	age = 0;
	totalCrystals = 0;
	totalShields = 0;
}

void Player::setName(string n)
{
	name = n;
}

string Player::getName()
{
	return name;
}

void Player::display()
{
	cout << "Name: " << name << endl;
	cout << "Age: " << age << endl;
}

//I need to get the inventory to display in a text box! That can be done below somehow

void Player::displayInventory()						//After class on 11/23 I don't think I need this method
{
	Item *current = inventory.getFirstElement();

	//cout << current << endl; //For testing

	if (current != 0)	//Items in the inventory
	{
		string inventTextList = current->getName();
		string fullList = " ";
		while (current != 0)
		{

			cout << current->getName() << endl;
			current = current->getNext();
			fullList = inventTextList + current->getName();
		}
		//Here we call the SDL_ShowMessageBox function which allows the programmer to
		//specify his/her own buttons. See: https://wiki.libsdl.org/SDL_ShowMessageBox
		string title = "Inventory";
		string message = "You are currently carrying: ";
		string items = current->getName();
		string allItems;
		while (current != 0)
		{
			current = current->getNext();
			allItems = items + current->getName();
		}
		//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
		//string buttonNames[2] = {"Take crystal", "Leave crystal"};
		const SDL_MessageBoxButtonData buttons[1] = {
			//{ 0, 1, "Leave crystal" }, //button with ID 1									
				{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Close Inventory" } //button with ID 0
		}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
		const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), fullList.c_str(), SDL_arraysize(buttons), buttons, NULL };
		//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
		int answer;
		SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button 
		if (answer == 0) //The user must have pressed the "Take crystal" button
		{
			cout << "Inventory Closed." << endl;
		}
	}
	else
	{
		cout << "Your inventory is empty." << endl;
	}
}

void Player::pickUpItem(Item* i)
{
	inventory.insert(i);
	PlaySound(TEXT("sounds//blop.wav"), NULL, SND_ASYNC);
}

int Player::getInventoryItems(string &items)
{
	items = "";
	Item *current = inventory.getFirstElement();
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

void Player::setHP(int h)
{
	HP = HP + h;
}

void Player::setGP(int g)
{
	GP = GP + g;
}