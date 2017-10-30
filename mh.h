#include <stdio.h>
#include <stdlib.h>
#include "room.h"
#include "player.h"
#include "zombies.h"

#ifndef mh_h_
#define mh_h_
#define KROOM_MAX 20

typedef struct tMH
{
	pRoom m_rooms[KROOM_MAX];
	int m_room_count;
	int m_done;
	pPlayer m_player;
	pZombie m_zombie1, m_zombie2, m_zombie3;
	char m_user_choice[11];
	int m_user_ichoice;
	int m_end_room_index;
	int m_valid;
} MH;

void MH_conversation(MH * rmh);
void MH_setup(MH * rmh);
void MH_hello(MH * rmh);
void MH_listen(MH * rmh);
void MH_respond(MH * rmh);
int MH_endcheck(MH * rmh);
void MH_cleanup(MH * rmh);
void set_room_exits(MH * rmh);
void set_player_location(MH * rmh);
void set_zombies_location(MH * rmh);
void show_player_exits(MH * rmh);
int cvt_choice_to_int(MH * rmh);
void move_player(MH * rmh);
void move_zombies(MH * rmh);
void set_end_room(MH * rmh);
void did_player_win(MH * rmh);
void did_zombie_attack_player(MH * rmh);
void is_zombie_close_by(MH * rmh);
void is_exit_close_by(MH * rmh);
int is_valid(MH * rmh);

#endif