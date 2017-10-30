// Author: Zachary McEachern
// email: zachmceachern@yahoo.com
// This program controls mystery house game.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "room.h"
#include "mh.h"
#include "player.h"
#include "zombies.h"
#define	DEATH_CHANCE 33

//Controls the mystery house game.
void MH_conversation(MH * rmh)
{
	//printf("Hello from MH_conversation!\n");
	MH_setup(rmh);
	MH_hello(rmh);
	do
	{
		MH_listen(rmh);
		MH_respond(rmh); 
	} while(MH_endcheck(rmh)); //Advance.

	MH_cleanup(rmh);
}

//Sets up the rooms for the game.
void MH_setup(MH * rmh)
{
#define KRS_SIZE 2 * 10
	int ix;
	pPlayer player;
	pZombie zombie1, zombie2, zombie3;
	char * room_strs[KRS_SIZE] =
	{"Kitchen", "a big kitchen full of antique rusted cookware.",
	"Reighleens_Room", "a room full of cute puppies.",
	"Hallway", "a dark hallway full of vines coming from the cieling and murals of mythical creatures.",
	"Aarons room", "a room full of videogame paraphernalia and old gaming consoles.",
	"Pantry", "a small room full of what looks like rotting food that no one has touched in years.",
	"Master_Bedroom", "a room that has a king sized bed in it with an ellaborate headboard.",
	"Basement", "a small dark room that only has a small dimly lit light hanging in the middle of it.",
	"Bathroom", "a small bathroom with a busted sink and dirty toilet. You can hardly stand the smell.",
	"Greenhouse", "a big open room with lots of different kinds of plants and very dirty windows that you can't see out of.",
	"Dining_Room", "a long room with a huge table in the middle that has atleast 20 chairs at it and the walls are lined with old portraits of people you don't know."
	};
	
	assert(rmh);

	player = (pPlayer)malloc(sizeof(Player));
	assert(player);
	rmh -> m_player = player;

	zombie1 = (pZombie)malloc(sizeof(Zombie));
	assert(zombie1);
	rmh -> m_zombie1 = zombie1;
	zombie2 = (pZombie)malloc(sizeof(Zombie));
	assert(zombie2);
	rmh -> m_zombie2 = zombie2;
	zombie3 = (pZombie)malloc(sizeof(Zombie));
	assert(zombie3);
	rmh -> m_zombie3 = zombie3;

	rmh -> m_room_count = 10;

	for(ix = 0;ix < rmh-> m_room_count;++ix)
	{
		rmh -> m_rooms[ix] = make_room(room_strs[ix*2], room_strs[(ix*2)+1]); //Advance.
		rmh -> m_rooms[ix] -> m_index = ix;
		//printf("Room: %s\nDescription: %s\n", rmh -> m_rooms[ix] -> m_title, rmh -> m_rooms[ix] -> m_desc);
	}

	set_room_exits(rmh);

	set_player_location(rmh);

	set_zombies_location(rmh);

	set_end_room(rmh);

	/*int count = 0;
	char filename[] = "House_Rooms.txt";
	FILE *ofp;
	char *mode = "r";

	printf("Hello from MH_setup!\n");

	ofp = fopen(filename, mode);

	if (ofp == NULL) {
		fprintf(stderr, "Cant open output file %s!\n");
		exit(1);
	}

	fscanf(ofp, "%d", &count);
	printf("%d\n", count);

	fclose(ofp); */
}

//Lets the user know that they are playing mystery house.
void MH_hello(MH * rmh)
{
	printf("You wake up in a room that you don't recognize and you have a slight headache.\n"
		"You hear a voice that whispers \"wElCOme tO ThE mYsTerY HOusE...\"\n");
}

//Gets the user's input and stores it.
void MH_listen(MH * rmh)
{
	//printf("Hello from MH_listen!\n");
	printf("You are in %s\n", rmh -> m_rooms[rmh -> m_player -> m_current_room] -> m_desc);
	show_player_exits(rmh);
	is_zombie_close_by(rmh);
	is_exit_close_by(rmh);
	do
	{
		
		printf("What next?> ");
		scanf("%s", rmh -> m_user_choice);
	}while(is_valid(rmh));
	//printf("%s\n", rmh -> m_user_choice); //DBG
}

//Responds to the users input and changes their current room along with the zombies.
void MH_respond(MH * rmh)
{
	//printf("Hello from MH_respond!\n");
	rmh -> m_user_ichoice = cvt_choice_to_int(rmh);
	//printf("%d\n", rmh -> m_user_ichoice); //DBG
	do
	{
		move_player(rmh);
		move_zombies(rmh);
		did_player_win(rmh);
		if(rmh -> m_done)
			break;
		did_zombie_attack_player(rmh);
	}while(0); //Once
}

//Checks wether the game ends or continues based on the users choice.
int MH_endcheck(MH * rmh)
{
	//printf("Hello from MH_endcheck!\n"); //DBG
	//rmh -> m_done = 0; //DBG
	return rmh -> m_done;
}

//Tells the user thanks for playing and cleans up the game.
void MH_cleanup(MH * rmh)
{
	int ix;
	printf("Thanks for playing!\n");

	for(ix = 0;ix < rmh -> m_room_count;++ix)
	{
		free(rmh -> m_rooms[ix]);
	}

	free(rmh -> m_player);
	free(rmh -> m_zombie1);
	free(rmh -> m_zombie2);
	free(rmh -> m_zombie3);
}

//Sets the exits that each room has.
void set_room_exits(MH * rmh)
{
	int ix, jx = 0;
	int random_exit_count;
	int random_exit = 0;
	//printf("Hello from set room exits!\n");

	for(ix = 0;ix < rmh -> m_room_count;++ix)
	{
		random_exit_count = (rand() % (7-3)+3); //Sets how many exits there will be between 3 and 7.

		while(jx < random_exit_count)
		{
			random_exit = (rand() % 9); //Chooses a random exit between 0 and 9.
			rmh -> m_rooms[ix] -> m_exits[random_exit] = rmh -> m_rooms[rand() % (rmh -> m_room_count)]; //Sets the rooms exits to go to other random rooms.
			++jx; //Advance while loop.
		}
		jx = 0; //Advance for loop.
	}
}

//Sets the players location in a random room.
void set_player_location(MH * rmh)
{
	int rand_room;
	//printf("Hello from set player location!\n");

	rand_room = (rand() % rmh -> m_room_count); //0 - room count.

	rmh -> m_player -> m_current_room = rand_room; //Places player in random starting room.
}

//Sets the 3 zombies in a random room that the user isn't in.
void set_zombies_location(MH * rmh)
{
	int rand_room;
	//printf("Hello from set zombies location!\n");

	do
	{
		rand_room = rand() % rmh -> m_room_count; //0 - room count.
		rmh -> m_zombie1 -> m_current_room = rand_room;
	}while(rmh -> m_player -> m_current_room == rmh -> m_zombie1 -> m_current_room ); //Sets first zombie's location.

	do
	{
		rand_room = rand() % rmh -> m_room_count; //0 - room count.
		rmh -> m_zombie2 -> m_current_room = rand_room;
	}while(rmh -> m_player -> m_current_room == rmh -> m_zombie2 -> m_current_room ); //Sets second zombie's location.

	do
	{
		rand_room = rand() % rmh -> m_room_count; //0 - room count.
		rmh -> m_zombie3 -> m_current_room = rand_room;
	}while(rmh -> m_player -> m_current_room == rmh -> m_zombie3 -> m_current_room ); //Sets third zombie's location.
}

void show_player_exits(MH * rmh)
{
	int ix;
	//printf("Hello from show player exits!\n");

	printf("There are exits to");

	for(ix = 0; ix < KEXITS_SIZE; ++ix)
	{
		if(rmh -> m_rooms[rmh -> m_player -> m_current_room] -> m_exits[ix] != 0) //Does the exit exist?
		{
			switch(ix)
			{
				case 0:
					{
						printf(" the North (N)");
						break;
					}
				case 1:
					{
						printf(", the Northeast (NE)");
						break;
					}
				case 2:
					{
						printf(", the East (E)");
						break;
					}
				case 3:
					{
						printf(", the Southeast (SE)");
						break;
					}
				case 4:
					{
						printf(", the South (S)");
						break;
					}
				case 5:
					{
						printf(", the Southwest (SW)");
						break;
					}
				case 6:
					{
						printf(", the West (W)");
						break;
					}
				case 7:
					{
						printf(", the Northwest (NW)");
						break;
					}
				case 8:
					{
						printf(", a rope ladder that leads Up (U)");
						break;
					}
				case 9:
					{
						printf(", and a sliding chute leads Downward (D)");
						break;
					}
				default:
					{
						//printf("---Invalid Input---\n");
						break;
					}
			}//Switch.
		}//If.
	}//For.
	printf(".\n");
}//Fcn.

//Converts the users exit direction selection into an integer.
int cvt_choice_to_int(MH * rmh)
{
	int choice_value = 0;

	if((strcmp(rmh -> m_user_choice, "N") == 0) || (strcmp(rmh -> m_user_choice, "North") == 0))
	{
		choice_value += 0;
	}
	else if((strcmp(rmh -> m_user_choice, "NE") == 0) || (strcmp(rmh -> m_user_choice, "Northeast") == 0))
	{
		choice_value += 1;
	}
	else if((strcmp(rmh -> m_user_choice, "E") == 0) || (strcmp(rmh -> m_user_choice, "East") == 0))
	{
		choice_value += 2;
	}
	else if((strcmp(rmh -> m_user_choice, "SE") == 0) || (strcmp(rmh -> m_user_choice, "Southeast") == 0))
	{
		choice_value += 3;
	}
	else if((strcmp(rmh -> m_user_choice, "S") == 0) || (strcmp(rmh -> m_user_choice, "South") == 0))
	{
		choice_value += 4;
	}
	else if((strcmp(rmh -> m_user_choice, "SW") == 0) || (strcmp(rmh -> m_user_choice, "Southwest") == 0))
	{
		choice_value += 5;
	}
	else if((strcmp(rmh -> m_user_choice, "W") == 0) || (strcmp(rmh -> m_user_choice, "West") == 0))
	{
		choice_value += 6;
	}
	else if((strcmp(rmh -> m_user_choice, "NW") == 0) || (strcmp(rmh -> m_user_choice, "Northwest") == 0))
	{
		choice_value += 7;
	}
	else if((strcmp(rmh -> m_user_choice, "U") == 0) || (strcmp(rmh -> m_user_choice, "Up") == 0))
	{
		choice_value += 8;
	}
	else if((strcmp(rmh -> m_user_choice, "D") == 0) || (strcmp(rmh -> m_user_choice, "Down") == 0))
	{
		choice_value += 9;
	}
	//else
		//printf("---Invalid Input---\n");
	return choice_value;
}

//Moves the player to the room that they chose.
void move_player(MH * rmh)
{
	//printf("Hello from move player\n");

	rmh -> m_player -> m_current_room = rmh -> m_rooms[rmh -> m_player -> m_current_room] -> m_exits[rmh -> m_user_ichoice] -> m_index; //Place player in their next room.
	//printf("You are in %s.\n", rmh -> m_rooms[rmh -> m_player -> m_current_room] -> m_desc); //DBG
}

//Moves the zombies to the next random room.
void move_zombies(MH * rmh)
{
	int random_exit_choice = 0;
	//printf("Hello from move zombie!\n");

	//Moves zombie1.
	do
	{
		random_exit_choice = rand() % 10;
		if(rmh -> m_rooms[rmh -> m_zombie1 -> m_current_room] -> m_exits[random_exit_choice]) //Does this exit exist?
			rmh -> m_zombie1 -> m_current_room = rmh -> m_rooms[rmh -> m_zombie1 -> m_current_room] -> m_exits[random_exit_choice] -> m_index; //Move zombie to his next room.
	}while(rmh -> m_rooms[rmh -> m_zombie1 -> m_current_room] -> m_exits[random_exit_choice] == 0);
	
	//Moves zombie2.
	do
	{
		random_exit_choice = rand() % 10;
		if(rmh -> m_rooms[rmh -> m_zombie2 -> m_current_room] -> m_exits[random_exit_choice]) //Does this exit exist?
			rmh -> m_zombie2 -> m_current_room = rmh -> m_rooms[rmh -> m_zombie2 -> m_current_room] -> m_exits[random_exit_choice] -> m_index; //Move zombie to his next room.
	}while(rmh -> m_rooms[rmh -> m_zombie1 -> m_current_room] -> m_exits[random_exit_choice] == 0);

	//Moves zombie3.
	do
	{
		random_exit_choice = rand() % 10; //0 - 9.
		if(rmh -> m_rooms[rmh -> m_zombie3 -> m_current_room] -> m_exits[random_exit_choice]) //Does this exit exist?
			rmh -> m_zombie3 -> m_current_room = rmh -> m_rooms[rmh -> m_zombie3 -> m_current_room] -> m_exits[random_exit_choice] -> m_index; //Move zombie to his next room.
	}while(rmh -> m_rooms[rmh -> m_zombie1 -> m_current_room] -> m_exits[random_exit_choice] == 0);
}

//Sets the final exit room.
void set_end_room(MH * rmh)
{
	int rand_room;
	//printf("Hello from set end room!\n"); //DBG

	do
	{
		rand_room = rand() % rmh -> m_room_count; //0 - room count.
		rmh -> m_end_room_index = rand_room; //Adv.
	}while(rmh -> m_player -> m_current_room == rmh -> m_end_room_index ); //Don't place the final room in the same room as the player.

	//printf("Player current room: %d End room: %d!\n", rmh -> m_player -> m_current_room, rmh -> m_end_room_index); //DBG
}

//Checks to see if the player beat the game.
void did_player_win(MH * rmh)
{
	//printf("Hello from did player win!\n"); //DBG

	if(rmh -> m_player -> m_current_room == rmh -> m_end_room_index) //Is the player in the end room?
	{
		rmh -> m_done = 0; //Player will now be exited from the game and return to the GM.
		printf("Congratulations! You have escaped! For now...\n"); //Player wins the game.
	}
	else
	{
		rmh -> m_done = 1; //Player will continue playing.
	}
}

//Checks to see if the playes is in the same room as one of the zombies and decides if the player lives or not.
void did_zombie_attack_player(MH * rmh)
{
	int death_roll = 0;
	death_roll = rand() % 101; //0 - 100.

	//printf("Hello from did zombie attack!\n"); //DBG
	if(rmh -> m_zombie1 -> m_current_room == rmh -> m_player -> m_current_room) //Is player in the same room as zombie1?
	{
		printf("As you open the door you see a giant zombie with a golden tooth wandering around the room and then it looks at you.\n");
		if(death_roll <= (DEATH_CHANCE * 2)) //Does the player die?
		{
			rmh -> m_done = 0;
			printf("The zombie runs towards you and attacks you and starts to eat your brain! Better luck next time...\n");
		}
		else
			printf("The zombie tries to attack you but you dodge it at the last second and get away!\n");
	}
	else if(rmh -> m_zombie2 -> m_current_room == rmh -> m_player -> m_current_room) //Is player in the same room as zombie2?
	{
		printf("As you open the door you see a zombie with half a head and a sword wandering around the room and then it looks at you.\n");
		if(death_roll <= DEATH_CHANCE) //Does the player die?
		{
			rmh -> m_done = 0;
			printf("The zombie runs towards you and cuts your head off and starts to eat your brain! Better luck next time...\n");
		}
		else
			printf("The zombie tries to swing it's sword at you but you dodge it at the last second and get away!\n");
	}
	else if(rmh -> m_zombie3 -> m_current_room == rmh -> m_player -> m_current_room) //Is player in the same room as zombie3?
	{
		printf("As you open the door you see a zombie with a wooden leg wandering around the room and then it looks at you.\n");
		if(death_roll <= (DEATH_CHANCE)/2) //Does the player die?
		{
			rmh -> m_done = 0;
			printf("The zombie hobbles towards you and attacks you and starts to eat your brain! Better luck next time...\n");
		}
		else
			printf("The zombie tries to attack you but you sweep it's wooden leg out from under him and get away!\n");
	}
}

//Checks if the a zombie is in the next room.
void is_zombie_close_by(MH * rmh)
{
	int ix;
	//printf("Hello from is zombie close by!\n"); //DBG
	for(ix = 0; ix < 10; ++ix)
	{
		if(rmh -> m_rooms[rmh -> m_player ->m_current_room] -> m_exits[ix])
		{
			if(rmh -> m_rooms[rmh -> m_player -> m_current_room] -> m_exits[ix] -> m_index == rmh -> m_zombie1 -> m_current_room) //Is zombie1 in the next room?
				printf("You hear the sound of really loud shuffling near by. You become extra cautious.\n");
			else if(rmh -> m_rooms[rmh -> m_player -> m_current_room] -> m_exits[ix] -> m_index == rmh -> m_zombie2 -> m_current_room) //Is zombie2 in the next room?
				printf("You hear shuffling near by and metal scraping along the ground.\n");
			else if(rmh -> m_rooms[rmh -> m_player -> m_current_room] -> m_exits[ix] -> m_index == rmh -> m_zombie3 -> m_current_room) //Is zombie3 in the next room? //Adv.
				printf("You hear a slight wooden tapping near by. You don't think much of it.\n");
		} //If.
	} //For.
} //Fcn.

//Checks if the exit is in one of the next rooms.
void is_exit_close_by(MH * rmh)
{
	int ix;
	//printf("Hello from is exit close by!\n"); //DBG
	for(ix = 0; ix < 10; ++ix)
	{
		if(rmh -> m_rooms[rmh -> m_player ->m_current_room] -> m_exits[ix])
		{
			if(rmh -> m_rooms[rmh -> m_player -> m_current_room] -> m_exits[ix] -> m_index == rmh -> m_end_room_index) //Adv.
				printf("You hear the sound of birds chirping and start to feel a sense of hope.\n");
		} //If.
	} //For.
}

//Makes sure the user's input is valid.
int is_valid(MH * rmh)
{
	int px;
	int exit;

	if((strcmp(rmh -> m_user_choice, "N") == 0) || (strcmp(rmh -> m_user_choice, "North") == 0))
	{
		px = 0;
	}
	else if((strcmp(rmh -> m_user_choice, "NE") == 0) || (strcmp(rmh -> m_user_choice, "Northeast") == 0))
	{
		px = 0;
	}
	else if((strcmp(rmh -> m_user_choice, "E") == 0) || (strcmp(rmh -> m_user_choice, "East") == 0))
	{
		px = 0;
	}
	else if((strcmp(rmh -> m_user_choice, "SE") == 0) || (strcmp(rmh -> m_user_choice, "Southeast") == 0))
	{
		px = 0;
	}
	else if((strcmp(rmh -> m_user_choice, "S") == 0) || (strcmp(rmh -> m_user_choice, "South") == 0))
	{
		px = 0;
	}
	else if((strcmp(rmh -> m_user_choice, "SW") == 0) || (strcmp(rmh -> m_user_choice, "Southwest") == 0))
	{
		px = 0;
	}
	else if((strcmp(rmh -> m_user_choice, "W") == 0) || (strcmp(rmh -> m_user_choice, "West") == 0))
	{
		px = 0;
	}
	else if((strcmp(rmh -> m_user_choice, "NW") == 0) || (strcmp(rmh -> m_user_choice, "Northwest") == 0))
	{
		px = 0;
	}
	else if((strcmp(rmh -> m_user_choice, "U") == 0) || (strcmp(rmh -> m_user_choice, "Up") == 0))
	{
		px = 0;
	}
	else if((strcmp(rmh -> m_user_choice, "D") == 0) || (strcmp(rmh -> m_user_choice, "Down") == 0))
	{
		px = 0;
	}
	else
	{
		//printf("---Invalid Input---\n");
		px = 1;
	}

	exit = cvt_choice_to_int(rmh);
	if(rmh -> m_rooms[rmh -> m_player -> m_current_room] -> m_exits[exit] == 0) //Was the user's choice one of the exits listed?
	{
		printf("---Invalid Input--- Please enter an exit listed\n");
		px = 1;
	}
	return px;
}