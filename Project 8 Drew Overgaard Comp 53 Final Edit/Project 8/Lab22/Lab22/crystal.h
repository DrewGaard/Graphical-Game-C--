//Project 8
//Drew Overgaard
//12/3/15


//FileName:		crystal.h
//Programmer:	Dan Cliburn
//Date:			9/15/2015
//Purpose:		This file defines the header for the Crystal class


#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "location.h"

class Crystal : public Location
{
	private:
		bool taken;

	public:
		Crystal(char s = 'C');

		int visit(Player &p);
		void draw(); //NOTE that draw will never get called in this lab activity

		void render(); //ADDED FOR THIS LAB ACTIVITY
}; //Do NOT forget this semicolon
#endif