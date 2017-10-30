// Author: Zachary McEachern
// email: zachmceachern@yahoo.com
// This program controlls the guess a card game.

#include <stdio.h>
#include <stdlib.h>
#include "nim.h"
#include "gm.h"
#include "gc.h"

//Controls the guess a card game.
void Gc_conversation(Gc * rgc)
{
	//printf("Hello from Gc_conversation!\n");
	Gc_setup(rgc);
	Gc_hello(rgc);
	do
	{
		Gc_listen(rgc);
		Gc_respond(rgc); 
	} while(Gc_endcheck(rgc)); //Advance.

	Gc_cleanup(rgc);
}

//Sets the random card for the game.
void Gc_setup(Gc * rgc)
{
	//printf("Hello from Gc_setup!\n");

	rgc -> m_secret = (rand() % (52-1+1)+1); //Creates a random integer from 1-52.
	//printf("The secret card # is: %d\n", rgc -> m_secret);
}

//Lets the user know that they are playing guess a card.
void Gc_hello(Gc * rgc)
{
	printf("Welcome to guess a card!\n"
		"Enter your card input as 'as' for 'Ace of Spades' or '2c' for '2 of clubs'\n");
}

//Gets the user's input and stores it.
void Gc_listen(Gc * rgc)
{
	printf("Enter your card choice: ");
	scanf("%s", rgc -> m_guess);
	printf("Your choice is %s\n", rgc -> m_guess);
}

//Calculates the delta and tells the user how far off they were from the secret card.
void Gc_respond(Gc * rgc)
{
	int delta = 0;

	//printf("Hello from Gc_respond!\n");

	rgc -> m_iguess = cvt_card_to_int(rgc); //Sets the converted user's guess to m_iguess.

	//printf("The users card converted to an int is: %d\n", rgc -> m_iguess);

	delta = ((rgc -> m_secret) - (rgc -> m_iguess)); //Calculates the delta between the user's guess and the game card.
	delta = abs(delta); //Gets the absolute value of the delta.
	rgc -> m_delta = delta; //Stores the delta in the class.
	printf("The difference between the game card and the card you chose is: %d\n", rgc -> m_delta);
	if (rgc -> m_delta == 0) //Delta greater than 0?
	{
		rgc -> m_exit = 0;
		printf("Congratulations you chose correctly!\n");
	}
}

//Checks wether the game ends or continues based on the users choice.
int Gc_endcheck(Gc * rgc)
{
	//printf("Hello from Gc_endcheck!\n");
	return rgc -> m_exit;
}

//Tells the user thanks for playing and cleans up the game.
void Gc_cleanup(Gc * rgc)
{
	printf("Thanks for playing!\n");
}

//Coverts the user's string entry to an integer.
int cvt_card_to_int(Gc * rgc)
{
	int card_value = 0;

	switch (rgc -> m_guess[0]) //What is the user's rank?
	{
	case 'a' :
		card_value += 13;
		break;
	case 'A' :
		card_value += 13;
		break;
	case '2' :
		card_value += 1;
		break;
	case '3' :
		card_value += 2;
		break;
	case '4' :
		card_value += 3;
		break;
	case '5' :
		card_value += 4;
		break;
	case '6' :
		card_value += 5;
		break;
	case '7' :
		card_value += 6;
		break;
	case '8' :
		card_value += 7;
		break;
	case '9' :
		card_value += 8;
		break;
	case '10' :
		card_value += 9;
		break;
	case 'j' :
		card_value += 10;
		break;
	case 'q' :
		card_value += 11;
		break;
	case 'k' :
		card_value += 12;
		break;
	case 'J' :
		card_value += 10;
		break;
	case 'Q' :
		card_value += 11;
		break;
	case 'K' :
		card_value += 12;
		break;
	default :
		printf("---Invalid Input---\n");
		return 0;
		break;
	}

	switch (rgc -> m_guess[1]) //What is the user's suit?
	{
	case 's' :
		card_value += 39;
		break;
	case 'h' :
		card_value += 26;
		break;
	case 'd' :
		card_value += 13;
		break;
	case 'c' :
		card_value += 0;
		break;
	case 'S' :
		card_value += 39;
		break;
	case 'H' :
		card_value += 26;
		break;
	case 'D' :
		card_value += 13;
		break;
	case 'C' :
		card_value += 0;
		break;
	default :
		printf("---Invalid Input---\n");
		return 0;
		break;
	}

	return card_value;
}