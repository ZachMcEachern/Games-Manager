#include <stdio.h>
#include <stdlib.h>
#include "nim.h"
#include "gc.h"
#include "mh.h"

#ifndef gm_h_
#define gm_h_

typedef struct tGm
{
	int m_data;
} Gm;

void Gm_conversation(Gm * rp, Gc * rgc, Nim * rnim, MH * rmh);
void Gm_setup(Gm * rp);
void Gm_hello(Gm * rp);
void Gm_listen(Gm * rp);
void Gm_respond(Gm * rp, Gc * rgc, Nim * rnim, MH * rmh);
int Gm_endcheck(Gm * rp);
void Gm_cleanup(Gm * rp);
void print_menu();

#endif