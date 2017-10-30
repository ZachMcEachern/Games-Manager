#include <stdio.h>
#include <stdlib.h>
#include "room.h"

#ifndef zombies_h_
#define zombies_h_

typedef struct tZombie
{
	int m_current_room;
}Zombie;
typedef struct tZombie * pZombie;

//void set_zombies_location(MH * rmh);

#endif