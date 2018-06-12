//FileName:		Videogame.cpp
//Programmer:	Dan Cliburn
//Date:			9/15/2015
//Purpose:		This file defines the methods for the Videogame class
//See:  http://www.sdltutorials.com/sdl-tutorial-basics/
//		http://www.sdltutorials.com/sdl-opengl-tutorial-basics/
//		http://www.sdltutorials.com/sdl-soundbank
//for many more details on how to write an OpenGL program using SDL.
//You might also want to go to these pages which will link you to other tutorials on how to do stuff with SDL.
//Be warned, however, that a lot of the tutorials describe SDL 1.2, but we will be using SDL 2 in this lab.

#include "videogame.h"
#include "texture.h"
#include <SDL.h>
#include <Windows.h>  //Must include this here to get it to compile
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <glut.h>  //includes gl.h and glu.h
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int MONITORWIDTH = 1200;
const int MONITORHEIGHT = 800;

//Static class variables
string Videogame::message1 = "";
string Videogame::message2 = "";
string Videogame::message3 = "";
string Videogame::message4 = "";

Videogame::Videogame()
{
	message1 = "";
	message2 = "";
	message3 = "";
	message4 = "";
}

//Initializes SDL and OpenGL
bool Videogame::init()
{
	display = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	if ((display = SDL_CreateWindow("Lab 21 Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MONITORWIDTH, MONITORHEIGHT, SDL_WINDOW_OPENGL)) == NULL)
	{
		return false;
	}
	oglcontext = SDL_GL_CreateContext(display);

	glClearColor(0.3, 0.3, 0.3, 1.0);  //Will be the color of the background
	
	//Set parameters for how we want to view the scene
	glViewport(0,0, MONITORWIDTH, MONITORHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Create a view frustum whose aspect ratio matches that of the window 
	double aspectRatio = ((double)(MONITORWIDTH)) / ((double)(MONITORHEIGHT));
	glFrustum(-0.1, 0.1, -0.1/aspectRatio, 0.1/aspectRatio, 0.1, 100);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Do OpenGL init stuff
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0); //Controls the thickness of lines

	//Now, initialize our other variables for drawing the game
	Eye[0] = Aim[0] = cols/2.0;
	Eye[2] = 1.28*rows;
	Aim[2] = rows/2.0;
	Eye[1] = rows/2.0;
	Aim[1] = 0.0;
	Up[0] = 0.0;
	Up[1] = 1.0;
	Up[2] = 0.0;

	//TODO: You need to make sure you use the same letter below as you assigned to the classes
	//in the game's setUpGame() method. For example, in setUpGame() the Fort object is assigned
	//the character 'F' for its symbol so the EXACT SAME letter needs to be sent below to the 
	//loader so that OpenGL knows to associate the fort.bmp image with the Fort class.
	Texture loader;
	loader.loadTexBMP("images//fort.bmp", (int)('F'), addAlpha);  //Image for the fort
	loader.loadTexBMP("images//crystal.bmp", (int)('C'), addAlpha);  //Image for the crystal
	
	loader.loadTexBMP("images//shield.bmp", (int)('S'), addAlpha);

	loader.loadTexBMP("images//shop.bmp", (int)('G'), addAlpha);

	loader.loadTexBMP("images//monster.bmp", (int)('M'), addAlpha);
	
	//TODO: Load more textures here for your other Location subclasses
	
	//NOTE: The image for the player should be loaded after you have loaded all of your images
	//for the locations. This ensures that the player image is assigned a texture ID different
	//than all of your location classes (which is what glGenTextures does).
	glGenTextures(1, &playerTexID); 
	loader.loadTexBMP("images//player.bmp", playerTexID, addAlpha);  //Image for the player	

	return true;  //Everything got initialized
}

//Method to draw an image associated with texID
void Videogame::renderBitMap(int texID)
{
	// make sure the transparent part of the texture isn't drawn
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	// select the texture
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
		// bottom left corner
		glTexCoord2f(0.0, 0.0); 
		glVertex3f(0.0, 0.0, 0.0);
					
		// bottom right corner
		glTexCoord2f(1.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);

		// top right corner
		glTexCoord2f(1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);
					
		// top left corner
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

//Draws the Heads Up Display (HUD) that shows players' info
void Videogame::drawHUD()
{
	unsigned int i;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Create a view frustum whose aspect ratio matches that of the window 
	double aspectRatio = ((double)(MONITORWIDTH)) / ((double)(MONITORHEIGHT));
	int width = 260;  //TODO:  Make this bigger if you need more space for your messages
	int height = width/aspectRatio;
	glOrtho(0, width, 0, height, -10, 10);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);  //COLOR OF THE TEXT MESSAGES
	glPushMatrix();
		glTranslatef(0.0, .95*height, 0.0);
		glScalef(0.05, 0.05, 0.05);
		for (i = 0; i < message1.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, message1[i]);
	glPopMatrix();
	
	//Message for the HP
	glPushMatrix();
		glTranslatef(0.0, .90*height, 0.0);
		glScalef(0.05, 0.05, 0.05);
		for (i = 0; i < message2.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, message2[i]);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, .85*height, 0.0);
		glScalef(0.05, 0.05, 0.05);
		for (i = 0; i < message3.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, message3[i]);
	glPopMatrix();

	//Message for the GP
	glPushMatrix();
	glTranslatef(0.40*width, .90*height, 0.0);
	glScalef(0.05, 0.05, 0.05);
	for (i = 0; i < message4.length(); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, message4[i]);
	glPopMatrix();


	//Put the program back in the proper projection for drawing the rest of the game
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.1, 0.1, -0.1/aspectRatio, 0.1/aspectRatio, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//This method draws the map of the world that the user sees
void Videogame::drawGame()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Establish the eye and aim positions, and the up vector 
	//The analogy is that of holding a digital camera and pointing it at what you want to take a picture of:
	//Eye is where the camera is at
	//Aim is what the camera is pointed at
	//Up is a vector that defines the up direction
	//NOTE: you do not need to change these parameters for Project 8
	gluLookAt(Eye[0],Eye[1],Eye[2], Aim[0],Aim[1],Aim[2], Up[0],Up[1],Up[2]);
 
	//Go through each location and render what the user should see
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (playerRow == r && playerCol == c) //Is this the square the player is at?
			{
				glColor3f(0.0, 0.5, 0.0);  //If so, then draw this square a different color
			}
			else
			{
				glColor3f(0.0, 0.0, 0.5); //color for ground locations the player has visited
			}
			if (world[r][c]->getVisited() == true || (playerRow == r && playerCol == c) )
			{	
				//Player has been to or is currently at this spot
				//Draw the green square that makes up the ground at a visited location
				glBegin(GL_QUADS);
					glVertex3f(c, 0.0, r);
					glVertex3f(c, 0.0, r+1.0);
					glVertex3f(c+1.0, 0.0, r+1.0);
					glVertex3f(c+1.0, 0.0, r);
				glEnd();
				
				//Now render what the player should see at this location
				glPushMatrix(); //Save the current transformation state
					glTranslatef(c, 0, r+0.7);
					world[r][c]->render(); //Go render the appropriate image (if any) for this location
				glPopMatrix();
			}
		}
	}

	//Now render the Player's Bitmap Image
	glPushMatrix(); //Save the current transformation state
		glTranslatef(playerCol, 0, playerRow+0.3);
		renderBitMap(playerTexID);
	glPopMatrix();

	//Draw the text messages. HUD stands for Heads Up Display
	drawHUD();
	
	SDL_GL_SwapWindow(display);
}

//This method handles user key presses on the keyboard
bool Videogame::handleEvent(SDL_Event *theEvent) 
{ 
	switch(theEvent->type)
	{
		case SDL_QUIT:  //User clicks on the 'X' in the Window
		{
			endGame();
			exit(0);
		}
		case SDL_KEYDOWN:
		{
			if (theEvent->key.keysym.sym == SDLK_DOWN && playerRow < rows - 1)
			{ 
				playerRow++;
			}
			if (theEvent->key.keysym.sym == SDLK_UP && playerRow > 0)
			{
				playerRow--;
			}
			if (theEvent->key.keysym.sym == SDLK_RIGHT && playerCol < cols - 1)
			{
				playerCol++;
			}
			if (theEvent->key.keysym.sym == SDLK_LEFT && playerCol > 0)
			{
				playerCol--;
			}
			else if (theEvent->key.keysym.sym == SDLK_h)
			{
				if (p.getGP() >= 6)
				{
					p.setHP(10);
					p.setGP(-6);
				}
			}
			//TODO: Add code so that the user can move left, right, and up
			
			//TODO: ADD CODE TO SUPPORT OTHER TYPES OF KEY PRESSES
			else if (theEvent->key.keysym.sym == SDLK_i)
			{
				string inventory;
				int totalItems;
				totalItems = p.getInventoryItems(inventory); //Method for project 8
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Inventory", inventory.c_str(), NULL);
				if (totalItems > 0)	//Add the code to see if the user wants to drop an item
				{
					Item *item;
					
					const SDL_MessageBoxButtonData buttons[2] = {
							{ 0, 1, "Yes" }, //button with ID 1
							{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "No" } //button with ID 0
					}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
					const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, "Inventory", "Do you want to drop an item?", SDL_arraysize(buttons), buttons, NULL };
					int answer;
					SDL_ShowMessageBox(&messageboxdata, &answer);
					if (answer == 1)	//If the user wants to drop an item in there inventory
					{
						const int MAX_INVENTORY_SIZE = 7;							//Make this the max number of items the user will be able to pickup in the game plus one, becasue of the cancel option
						SDL_MessageBoxButtonData buttonData[MAX_INVENTORY_SIZE];
						char buttonNames[MAX_INVENTORY_SIZE][20];
						for (int i = totalItems; i > 0; i--)
						{
							buttonData[i].flags = 0;
							buttonData[i].buttonid = i;
							item = p.getInventoryItem(i-1);
							if (item != 0)
							{
								strcpy_s(buttonNames[i], item->getName().c_str());
								buttonData[i].text = buttonNames[i];
							}
							else
							{
								buttonData[i].text = "OOPS";
							}
						}
						buttonData[0].flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
						buttonData[0].buttonid = 0;
						buttonData[0].text = "CANCEL";
						
						//Show the message box to the user
						const SDL_MessageBoxData messageboxdata2 = { SDL_MESSAGEBOX_INFORMATION, NULL, "Inventory", "Click on the item that you wish to drop.", totalItems + 1, buttonData, NULL };
						SDL_ShowMessageBox(&messageboxdata2, &answer);	//Answer holds the id of the pressed buttton

						if (answer != 0) //If the user pressed 0 then they must have pressed the cancel button
						{
							item = p.getInventoryItem(answer - 1);
							if (item != 0)
							{
								item = p.dropItem(item->getName());
								if (item != 0)
								{
									world[playerRow][playerCol]->putItemOnGround(item); //Insert the item into the ground list
								}
							}
						}
					}
				}

				//cout << "You are carrying: " << endl;
				//p.displayInventory();
				/*
				Item *i = p.dropItem();
				if (i != 0)
				{
					world[playerRow][playerCol]->placeOnGround(i);
				}
				*/
			}
			else
			{
				message3 = "You can't do that!";
				drawGame();
				Sleep(1000); //Show the error message for one second
			}
			return true;
		}
	} 
	return false; //was not a KEYDOWN event
}

//This method controls the game
void Videogame::playGame()
{
	int state = 1;

	instructions(); //Tell the player how to play the game
	setUpGame();  //call setUpGame() from the Game class

	if (!init()) //This function (defined above) sets up OpenGL and SDL
	{
		cout << "Not everything was initialized" << endl;
		return;
	}

	SDL_Event events;  //Makes an SDL_Events object that we can use to handle events
	SDL_PollEvent(&events); //This initializes the events object
	while (state != 10) //the game continues as long as state is not 10 (which means the player found the fort)
	{
		//Build message strings for the HUD (Head's Up Display)
		message1 = p.getName() + ", use the arrow keys to move.";
		stringstream out2;
		stringstream out4;
		out2 << p.getHP();
		out4 << p.getGP();
		message2 = "Your HP is " + out2.str();
		message4 = "You have " + out4.str() + " GP";

		drawGame(); //draw the current state of the game

		do
		{
			SDL_WaitEvent(&events); //wait here until there is an event to handle
		} while (handleEvent(&events) == false); //keep looping if event was something other than a KEYDOWN 
		drawGame(); //update the user's position on the gameboard

		//reset message strings and resolve actions involved with the move
		message1 = message2 = message3 = "";
		state = world[playerRow][playerCol]->visit(p);

		//TODO: This would be a good place to deal with picking up items that are at this location
		world[playerRow][playerCol]->displayGround(); //For testing
		world[playerRow][playerCol]->takeFromGround(p);

		if (p.getHP() <= 0)
		{
			string title = "You Have Been Defeated";
			string message = "You ran out of HP and have died. You did not make it back to you dimension.";
			//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
			//string buttonNames[2] = {"Take crystal", "Leave crystal"};
			const SDL_MessageBoxButtonData buttons[2] = {
					{ 0, 1, "Try Again" }, //button with ID 1
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Exit" } //button with ID 0
			}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
			const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
			//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
			int answer;
			SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button 
			if (answer == 1) //The user must have pressed the "Take crystal" button
			{
				endGame();
				Videogame n;	
				n.playGame();
				//exit(0);
			}
			else if (answer == 0)
			{
				endGame();
				exit(0);
			}
		}
	}
	drawGame(); //Draw the game one last time before the program ends
	Sleep(4000); //Pause for 4 seconds before ending the game
	endGame();
	system("pause");
}

void Videogame::instructions()
{
	//In this example we use the SDL_ShowSimpleMessageBox function to display instructions to the user. 
	//See: https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
	string message = "Hello! Our records show that you travelled here from an alternate dimension.\nUnfortunately you picked a bad time to visit, as we have recently been invaded by alien robots.\n";
	message += "If you want to get back home you'll need to find your way to the nearest time portal.\nYou might run into some of those nasty alien robots on the way so be prepared to fight.";
	message += "\nTo walk around the map use the arrow keys.\nYou can press the 'i' key during the game to see your inventory and drop items.\nYou can also press the 'h' key to heal yourself, but it'll cost you 10GP.\nYou can also pickup items off the ground if any exist.";
	message += "\nDefeat alien robots to earn GP, but make sure your HP does not got to 0.\nYou may come across a shop where you can use your GP to purchase items.";
	string title = "Welcome";
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
	 //NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION

	//Check to see if the user wants to play. Here we will use the SDL_ShowMessageBox function which allows the programmer to
	//specify his/her own buttons. See: https://wiki.libsdl.org/SDL_ShowMessageBox
	title = "Question?";
	message = "Do you want to attempt to get to the time portal and go back home?";
	//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
	const SDL_MessageBoxButtonData buttons[3] = { 
			{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "CANCEL" }, //button with ID 2
			{0, 1, "NO"}, //button with ID 1
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "YES" } //button with ID 0
	}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
	const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
										//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
	int answer;
	do
	{
		SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button
		if (answer == 1) //The user must have pressed the "NO" button
		{
			endGame();
			exit(0);
		}
		else if (answer == 2 || answer == -1) //The user must have pressed the "CANCEL" button or closed the Window
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Uh oh!", "You have to select YES or NO", NULL);
		}
	} while (answer != 0); //Loop until the user selects to play since the ID for "YES" is 0

	//We can still use the console to get input from the user until our graphics window is created (which happens as soon as this method ends).
	string name;
	cout << "Please enter your name: ";
	cin >> name;
	p.setName(name);
}

void Videogame::endGame()
{
	SDL_GL_DeleteContext(oglcontext);
	SDL_DestroyWindow(display);
	SDL_Quit();
}