#include "registry.h"

int nb_to_read(char *buf)
{
	if(strncmp(buf, "regf", 4) == 0)
		return 4096;

	return 0;
}
