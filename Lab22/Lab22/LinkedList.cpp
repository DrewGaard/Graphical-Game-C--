//Drew Overgaard
//Comp 53
//Project 6

#include "LinkedList.h"
#include "Item.h"

void LinkedList::insert(Item *p)
{
	if (head == 0)	//Case 1 check if the list is empty
	{
		head = p;
	}
	else if (p->getName() < head->getName())	//Case 2 thing needs to go at the begining of the list
	{							//These statements must be in this order
		p->setNext(head);
		head = p;
	}
	else			//Need to search through the list
	{
		Item *current = head;
		while (current->getNext() != 0 && current->getNext()->getName() < p->getName())		//Check for where the new item should go in the list
		{
			current = current->getNext();
		}

		p->setNext(current->getNext());
		current->setNext(p);
	}
}

Item *LinkedList::remove(string key)
{
	if (head == 0)	//The list is empty
	{
		return 0;	//Didn't find the key
	}
	else if (head->getName() == key)	//Remove the first thing in the list
	{
		Item *temp = head;
		head = head->getNext();
		temp->setNext(0);	//Make this item no longer point to anything else since it's not part of the list
		return temp;
	}
	else	//Need to search through the list using linear search
	{
		Item *current = head;
		while (current->getNext() != 0)	//Loop until we reach the end of the list
		{
			if (current->getNext()->getName() == key)
			{
				Item *temp = current->getNext();
				current->setNext(temp->getNext());
				temp->setNext(0);
				return temp;
			}
			current = current->getNext();	//Make current move to the next item in the list
		}
		return 0; //Item was not in the list
	}
}

Item *LinkedList::find(string key)
{
	Item *current;
	current = head;
	while (current != 0)
	{
		if (current->getName() == key)
		{
			return current;
		}
		current = current->getNext();
	}
	return 0;
}

Item *LinkedList::find(int key)
{
	Item *current = head;
	int total = 0;

	while (current != 0) //List is not empty
	{
		if (total == key)
		{
			return current;
		}
			current = current->getNext();
			total++;
	}
	return 0;		//List was empty or the item was not found
}

Item *LinkedList::getFirstElement()
{
	return head;
}

LinkedList::~LinkedList()
{
	Item *temp;
	while (head != 0) //While elements exist in the list
	{
		temp = head;
		head = head->getNext();
		delete temp;
	}
}

void LinkedList::print()
{
	Item* temp = head;
	cout << temp->getName() << endl;
}