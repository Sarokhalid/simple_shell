#include "shell.h"
void ex_comm(const char *comm)
{
	while (*comm == ' ' || *comm == '\t')
		comm++;
	if (*comm == '\0' || *comm == '#')
		return;
	system(comm);
}

	
