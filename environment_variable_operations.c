#include "shell.h"

char *_getenv(const char *name)
{
	size_t nameLength = _strlen(name);
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(name, environ[i], nameLength) == 0 &&
				environ[i][nameLength] == '=')
		{
			return (environ[i] + nameLength + 1);
		}
	}

	return (NULL);
}
