#include <types.h>
#include <libc/stdio.h>

char tab[23] = "tagbeginvar1,var2tagend";

void user_receive (uint8_t t)
{
   printf ("Je recois la valeur %d\n", t);
}
