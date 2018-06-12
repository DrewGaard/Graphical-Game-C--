//FileName:		crystal.h
//Programmer:	Dan Cliburn
//Date:			9/15/2015
//Purpose:		This file defines the header for the Crystal class

#ifndef SHIELD_H
#define SHIELD_H

#include "location.h"

class Shield : public Location
{
private:
	bool taken;

public:
	Shield(char s = 'S');

	int visit(Player &p);
	void draw(); //NOTE that draw will never get called in this lab activity

	void render(); //ADDED FOR THIS LAB ACTIVITY
}; //Do NOT forget this semicolon
#endif