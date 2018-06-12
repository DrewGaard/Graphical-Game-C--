//Drew Overgaard
//Comp 53
//Project 7

#ifndef MONSTER_H
#define MONSTER_H

#include "location.h"


class Monster : public Location
{
protected:
	bool taken;

public:
	Monster(char M);

	void setTaken(bool t);
	bool getTaken();
	void render();

	void draw();
	int visit(Player &p);				//Pass in the player object so we know when the player has visited a location
};

#endif