#include <types.h>
#include <libc/stdio.h>

uint8_t toto = 0;

void user_send (uint8_t* t)
{
   *t = toto;
   printf ("J'envoie la valeur %d\n", toto);
   toto++;
}
