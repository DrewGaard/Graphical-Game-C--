//Project 8
//Drew Overgaard
//12/3/15

#ifndef ITEM_HEADER
#define ITEM_HEADER

#include <iostream>
#include <string>

using namespace std;

class Item
{
private:
	string name;
	Item *next;

public:
	Item(string n = " ") { name = n, next = 0; }

	void setName(string n) { name = n; }
	void setNext(Item *n) { next = n; }

	string getName() { return name; }
	Item *getNext() { return next; }
};

#endif