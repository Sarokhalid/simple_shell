#include "shell.h"

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

size_t _strcpy(char *dest, const char *src)
{
	char *save = dest;

	while ((*dest++ = *src++))
		;
	return (dest - save - 1);
}

char *_strcat(char *dest, const char *src)
{
	char *save = dest;

	while (*dest)
		dest++;
	while ((*dest++ = *src++))
		;
	return (save);
}
