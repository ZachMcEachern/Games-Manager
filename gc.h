#include <stdio.h>
#include <stdlib.h>

#ifndef gc_h_
#define gc_h_

typedef struct tGc
{
	int m_exit;
	char m_guess[10];
	int m_secret;
	int m_delta;
	int m_iguess;
} Gc;

void Gc_conversation(Gc * rgc);
void Gc_setup(Gc * rgc);
void Gc_hello(Gc * rgc);
void Gc_listen(Gc * rgc);
void Gc_respond(Gc * rgc);
int Gc_endcheck(Gc * rgc);
void Gc_cleanup(Gc * rgc);
int cvt_card_to_int(Gc *rgc);

#endif