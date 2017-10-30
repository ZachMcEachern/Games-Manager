// Author: Zachary McEachern
// email: zachmceachern@yahoo.com
// This program manages all of the games within this program.

#include <stdio.h>
#include <stdlib.h>
#include "nim.h"
#include "gm.h"
#include "gc.h"
#include "mh.h"

// Conversates with the user.
void Gm_conversation(Gm * rp, Gc * rgc, Nim * rnim, MH * rmh)
{
	//printf("Hello from Gm_conversation\n");

	do
	{
		Gm_setup(rp);
		Gm_hello(rp);
		Gm_listen(rp);
		Gm_respond(rp, rgc, rnim, rmh);
	} while(Gm_endcheck(rp));

	Gm_cleanup(rp);
}

// Sets up any part of a game that might need to happen.
void Gm_setup(Gm * rp)
{
	//printf("Hello from Gm_setup\n");
}

// Tells user that they are dealing with the Gm.
void Gm_hello(Gm * rp)
{
	//printf("Hello this is the GM!\n");
}

// Prints the menu and gets user response.
void Gm_listen(Gm * rp)
{
	int ax;
	//printf("Hello from Gm_listen\n");
	print_menu();
	scanf("%d", &ax); // Gets user input on menu choice.
	rp -> m_data = ax; // Sets m_data value to user's menu choice.
}

// Goes to whichever game the user chose or exits the program.
void Gm_respond(Gm * rp, Gc * rgc, Nim * rnim, MH * rmh)
{
	//printf("Hello from Gm_respond\n");
	switch (rp -> m_data) // What was user's menu choice?
	{
	case 1 :
		Gc_conversation(rgc);
		break;
	case 2 :
		//printf("Game 2 is under construction\n");
		Nim_conversation(rnim);
		break;
	case 3 :
		//printf("Game 3 is under construction\n");
		MH_conversation(rmh);
		break;
	case 0 :
		printf("Thanks for playing!\n");
		break;
	default :
		printf("--Invalid Input-- Please enter one of the menu options\n");
		break;
	}
}

//  Checks that the user still wants to play or leave.
int Gm_endcheck(Gm * rp)
{
	//printf("Hello from Gm_endcheck\n");
	return rp -> m_data; // Returns users choice.
}

// Saves any scores from the game they played.
void Gm_cleanup(Gm * rp)
{
	//printf("Hello from Gm_cleanup\n");
}

// Prints the menu.
void print_menu()
{
	printf("Choose a game:\n"
	"1: Guess a card\n"
	"2: Nim\n"
	"3: Mystery House\n"
	"0: Quit\n"
	"> ");
}