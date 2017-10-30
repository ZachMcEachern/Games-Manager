#include <stdio.h>
#include <stdlib.h>

#ifndef room_h_
#define room_h_

#define KEXITS_SIZE 11

typedef struct troom * pRoom;
typedef struct troom
{
	pRoom mMH_next_room;
	char * m_title;
	char * m_desc;
	pRoom m_exits[KEXITS_SIZE];
	int m_has_zombie;
	int m_has_player;
	int m_has_exit;
	int m_exit;
	int m_index;
} Room;

pRoom make_room(char * rt, char * rd);

#endif 