#include "shell.h"

void handle_comments(char *cmd)
{
	char *cs = _strchr(cmd, '#');

	if (cs != NULL)
	{
		*cs = '\0';
	}
}

