//Project 8
//Drew Overgaard
//12/3/15

//FileName:		fourt.cpp
//Programmer:	Dan Cliburn
//Date:			2/4/2013
//Purpose:		This file defines the methods for the fourt class

#include "fort.h"
#include "player.h"
#include "videoGame.h"
#include <Windows.h>
#include <mmsystem.h>

//The draw method is not going to be used in this lab activity.  
//Instead, we will call the render method (defined below)
void Fort::draw()
{
	if (visited == false)
	{
		cout << ".";
	}
	else
	{
		cout << "F";
	}
}

int Fort::visit(Player &p)
{
	if (visited == false)
	{
		PlaySound(TEXT("sounds//tada.wav"), NULL, SND_ASYNC);
		Videogame::setMessage1("Hurray! " + p.getName() + ", you found the Time Portal!");
		//cout << p.getName() << " found the Fourt!" << endl;  system("pause");  //NOTICE HOW THE METHOD IS MODIFIED FOR THIS LAB ACTIVITY
	}
	visited = true;
	return 10;  //10 is for a fourt
}