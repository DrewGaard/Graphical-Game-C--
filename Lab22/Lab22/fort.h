//FileName:		fort.h
//Programmer:	Dan Cliburn
//Date:			2/4/2013
//Purpose:		This file defines the header for the Fourt class

#ifndef FORT_H
#define FORT_H

#include "location.h"
#include "player.h"

class Fort : public Location
{
	public:
		Fort(char s = 'F') : Location(s) { ; }

		int visit(Player &p);
		void draw(); //NOTE that draw will never get called in this lab activity
};
#endif