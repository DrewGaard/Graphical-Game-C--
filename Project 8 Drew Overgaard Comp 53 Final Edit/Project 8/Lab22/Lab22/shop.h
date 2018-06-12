//Project 8
//Drew Overgaard
//12/3/15

#ifndef SHOP_H
#define SHOP_H

#include "location.h"


class Shop : public Location
{
protected:
	bool taken;
	char symbol = 'G';

public:
	Shop(char G);

	void setTaken(bool t);
	bool getTaken();

	void draw();
	int visit(Player &p);				//Pass in the player object so we know when the player has visited a location
};

#endif