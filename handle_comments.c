#include "shell.h"
/**
 * handle_comments - Removes comments from a command string.
 * @cmd: The command string to be processed.
 * Description: This function removes comments
 * from a command string by replacing the '#' character
 * and everything after it with a null terminator.
 * If no '#' character is found,the function does nothing.
 **/

void handle_comments(char *cmd)
{
	char *cs = _strchr(cmd, '#');

	if (cs != NULL)
	{
		*cs = '\0';
	}
}

