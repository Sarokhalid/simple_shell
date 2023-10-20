#include "shell.h"
/**
 * _getenv - Retrieves the value of an environment variable.
 * @name: The name of the environment variable.
 * @env: The environment variables array
 * Return: A pointer to the value of the environment variable
 * or NULL if not found.
 **/

char *_getenv(const char *name, char **env)
{
	size_t nameLength = _strlen(name);
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (_strncmp(name, env[i], nameLength) == 0 &&
				env[i][nameLength] == '=')
		{
			return (env[i] + nameLength + 1);
		}
	}

	return (NULL);
}
