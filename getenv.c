#include "shell.h"
char *_getenv(const char *name)
{
	extern char **environ;
	size_t vl;
	int k;

	vl = _strlen(name);
	for (k = 0; environ[k] != NULL; k++)
	{
		if (_strncmp(name, environ[k], vl) == 0 && environ[k][vl] == '=')
			return (environ[k] + vl + 1);
	}
	return (NULL);
}

size_t _strlen(const char *s)
{
	size_t l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

int _strncmp(const char *s, const char *ss, size_t n)
{
	size_t y = 0;
	while (s[y] != '\0' && ss[y] != '\0' && y < n)
	{
		if (s[y] != ss[y])
			return (s[y] - ss[y]);
		y++;
	}
	if (y == n)
		return (0);
	return (s[y] - ss[y]);
}
