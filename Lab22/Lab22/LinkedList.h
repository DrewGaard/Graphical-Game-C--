#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

#include <iostream>
#include "Item.h"

using namespace std;

class LinkedList
{
private:
	Item *head;

public:
	LinkedList() { head = 0; }	//Setting a pointer equal to zero is how we make it point to nothing
	void insert(Item *p);
	Item *remove(string key);
	Item *find(string key);
	Item *find(int itemNum);
	Item *getFirstElement();
	void print();
	~LinkedList();
};

#endif