#include <stdio.h>
#include <stdlib.h>

#ifndef nim_h_
#define nim_h_

typedef struct tNim
{
	int user_row;
	int user_count;
	int board[10];
	int rowcount;
	int total_pebbles;
	char winner;
} Nim;

void Nim_conversation(Nim * rnim);
void Nim_setup(Nim * rnim);
void Nim_hello(Nim * rnim);
void Nim_listen(Nim * rnim);
void Nim_respond(Nim * rnim);
int Nim_endcheck(Nim * rnim);
void Nim_cleanup(Nim * rnim);
void Nim_brain_moves(Nim * rnim);
void is_move_valid(Nim * rnim);

#endif