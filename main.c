// Author: Zachary McEachern
// email: zachmceachern@yahoo.com
// This program asks a user which game he wants to play and then runs the game of their choice. 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nim.h"
#include "gm.h"
#include "gc.h"
#include "mh.h"

// Creates the Gm class.
int main()
{
	Gm gmx;
	Gc gmy;
	Nim gmz;
	MH mhw;

	srand(time(NULL)); //Randomizes the rand function based on time.

	Gm_conversation(&gmx, &gmy, &gmz, &mhw); 

	//printf("Hello From Main\n");
	
	return 0;
}