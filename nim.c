// Author: Zachary McEachern
// email: zachmceachern@yahoo.com
// This program plays the game "nim" with the user.

#include <stdio.h>
#include <stdlib.h>
#include "nim.h"

//Controlls the nim game.
void Nim_conversation(Nim * rnim)
{
	//printf("Hello from Conv!\n");
	Nim_setup(rnim);
	Nim_hello(rnim);
	do
	{
		Nim_listen(rnim);
		Nim_respond(rnim); 
		if(rnim -> total_pebbles == 0) //Did the user win?
			break;
		Nim_brain_moves(rnim);
		Nim_respond(rnim);
	} while(Nim_endcheck(rnim)); //Advance.

	Nim_cleanup(rnim);
}

//Sets up the nim game.
void Nim_setup(Nim * rnim)
{
	int i, j;
	rnim -> total_pebbles = 0;
	rnim -> rowcount = (rand() % (5-3)+3); //Gets a random number of rows inbetween 3 and 5.
	//int pebblecount = (rand() % (8-2+2)+2);
	//int board[10];

	//printf("Hello from setup!\n");
	//printf("%d", rnim -> rowcount);

	for(i = 0; i < rnim -> rowcount; i++)
	{
		rnim -> board[i] = (rand() % (8-2)+2); //Sets a random number of pebbles for that row between 2 and 8.
		rnim -> total_pebbles += rnim -> board[i]; //Adds the number of pebbles in that row to the total ammount of pebbles.
		printf("\n%d: ", i);
		for(j = 0; j < rnim -> board[i]; j++) //Prints the pebbles on the board.
		{
			printf("o");
		}
	}
	printf("\n");
	//printf("Total Pebbles: %d\n", rnim -> total_pebbles);
}

//Tells the user the rules.
void Nim_hello(Nim * rnim)
{
	//printf("Hello from Hello!\n");
	printf("Rules: on your turn you must pick a non-empty row and remove one or more pebbles, up to all of them.\n");
}

//Gets the user's input.
void Nim_listen(Nim * rnim)
{
	//printf("Hello from listen!\n");

	rnim -> winner = 'u';
	is_move_valid(rnim);
	if(rnim -> user_count == 1)
		printf("You take %d pebble from row %d.\n", rnim -> user_count, rnim -> user_row);
	else
		printf("You take %d pebbles from row %d.\n", rnim -> user_count, rnim -> user_row);
	//printf("Row: %d, Count: %d\n", rnim -> user_row, rnim -> user_count);
}

//Dsiplays the updated nim board.
void Nim_respond(Nim * rnim)
{
	int i, j;
	//printf("Hello from respond!\n");

	if(rnim -> user_count <= rnim -> board[rnim -> user_row]) //Did user guess below how many pebbles are in that row?
	{
		rnim -> board[rnim -> user_row] -= rnim -> user_count; //Subtract the number of pebbles from the board.
		rnim -> total_pebbles -= rnim -> user_count; //Subtract that amount of pebbles from the total amount.
	}
	else if(rnim -> user_count > rnim -> board[rnim -> user_row]) //Did the user guess more than the ammount of pebbles in that row?
	{
		rnim -> total_pebbles -= rnim -> board[rnim -> user_row]; //Subtract that row's pebbles from the total ammount of pebbles.
		rnim -> board[rnim -> user_row] = 0; //Set that row's pebbles to 0.
	}
	for(i = 0; i < rnim -> rowcount; i++)
	{
		//rnim -> board[i] = (rand() % (8-2)+2);
		printf("\n%d: ", i);
		for(j = 0; j < rnim -> board[i]; j++)
		{
			printf("o");
		}
	}
	printf("\n");
	//printf("Total Pebbles: %d\n", rnim -> total_pebbles);
}

//Checks to see if the brain won.
int Nim_endcheck(Nim * rnim)
{
	//printf("Hello from endcheck!\n");

	if(0 == rnim -> total_pebbles) //Are there any pebbles left?
		return 0;
}

//Tells the user who won.
void Nim_cleanup(Nim * rnim)
{
	//printf("Hello from cleanup!\n");
	//printf("Winner: %c\n", rnim -> winner);

	if(0 == rnim -> total_pebbles) //Make sure the game is over.
	{
		switch (rnim -> winner) //Who won this game?
		{
		case 'u': //The user?
			printf("Congratulations! You've won Nim!\n");
			break;
		case 'b': //The brain?
			printf("I have beaten you, better luck next time!\n");
			break;
		}
	}
}

//The brain takes it's turn in the nim game.    
void Nim_brain_moves(Nim * rnim)
{
	//printf("Hello from Brain moves!\n");

	rnim -> winner = 'b'; //Set the winner to be the brain if the game ends on this turn.
	do
	{
		rnim -> user_row = (rand() % (rnim -> rowcount)); //The brain selects a row.
		if(rnim -> board[rnim -> user_row] != 0) //Is the row empty?
			break;
	}while(rnim -> board[rnim -> user_row] == 0); //Continue till a non empty row is found.

	rnim -> user_count = (rand() % (8-1)+1); //The brain selects a randon number of pebbles.

	if(rnim -> user_count == 1)
		printf("I take %d pebble from row %d.\n", rnim -> user_count, rnim -> user_row);
	else
		printf("I take %d pebbles from row %d.\n", rnim -> user_count, rnim -> user_row);
}

//Checks to make sure that the user inputs a valid number.
void is_move_valid(Nim * rnim)
{
	rnim -> user_row = -1;
	rnim -> user_count = -1;
	while(rnim -> board[rnim -> user_row] == 0 || rnim -> user_row < 0) //Is the chosen row empty? Or did the user choose a negative number?
	{
		printf("Row: ");
		scanf("%d", &rnim -> user_row); //Gets user's row number.
		if(rnim -> board[rnim -> user_row] == 0 || rnim -> user_row < 0)
			printf("---Invalid Entry--- Please enter a valid non-empty row number\n");
	}

	while(rnim -> user_count <= 0) //Did the user enter in a negative number?
	{
		printf("Count: ");
		scanf("%d", &rnim -> user_count); //Gets user'c count number.
		if(rnim -> user_count <= 0)
			printf("---Invalid Entry--- Please enter in a positive number.\n");
	}
}