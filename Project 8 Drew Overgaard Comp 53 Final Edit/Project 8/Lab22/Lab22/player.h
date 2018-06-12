//Project 8
//Drew Overgaard
//12/3/15
//FileName:		player.h
//Programmer:	Dan Cliburn
//Date:			9/15/2015
//Purpose:		This file defines the header for the player class

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "LinkedList.h"
using namespace std;

class Player
{
	protected: //attributes usually go here
		string name;
		int age;
		int totalCrystals;
		int totalShields;
		int HP = 50;
		int GP = 0;
		LinkedList inventory;

	public:  //method prototypes usually go here
		Player(string n = "Dan");

		//Set methods allow objects to change the attributes
		void setName(string n);
		void setAge(int a) {age = a;}
		void setTotalCrystals(int c) { totalCrystals = c; }
		void setTotalShields(int s) { totalShields = s; }
		void setHP(int s);
		void setGP(int g);

		//Get methods allow objects to tell us about their attributes
		string getName();
		int getAge() {return age;}
		int getTotalCrystals() { return totalCrystals; }
		int getTotalShields() { return totalShields; }
		int getHP() { return HP; }
		int getGP() { return GP; }

		//Functionality methods are additional actions of objects of the class
		void display();
		void displayInventory();
		void pickUpItem(Item* i);
		int getInventoryItems(string &items);
		Item *getInventoryItem(int i) { return inventory.find(i);  }
		Item *dropItem(string name) { return inventory.remove(name);  }
};

#endif