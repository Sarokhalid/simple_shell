#include "shell.h"
/**
 * _getenv - Retrieves the value of an environment variable.
 * @name: The name of the environment variable.
 * Return: A pointer to the value of the environment variable
 * or NULL if not found.
 **/

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
