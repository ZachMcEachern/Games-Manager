// Author: Zachary McEachern
// email: zachmceachern@yahoo.com
// This program controlls the rooms of the mystery house.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "room.h"
#include "mh.h"
#include "player.h"
#include "zombies.h"

//Makes the room obects;
pRoom make_room(char * rt, char * rd)
{
	pRoom px;
	int ix;

	//printf("Hello from make_room!\n");

	px = (pRoom) malloc(sizeof(Room));
	assert(px);
	px -> m_title = rt;
	px -> m_desc = rd;

	for(ix = 0; ix < KEXITS_SIZE; ++ix)
	{
		px -> m_exits[ix] = 0;
	}

	return px;
}