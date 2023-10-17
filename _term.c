#include "shell.h"

char *_trim(char *str)
{
	char *st = str;
	char *en = str + _strlen(str) - 1;

	if (str == NULL)
		return (NULL);
	while (_isspace(*st))
		st++;
	while (en > st && _isspace(*en))
		en--;
	*(en + 1) = '\0';
	return (st);
}

int _isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}

int _dup2(int oldfd, int newfd)
{
	if (oldfd == newfd)
	{
		return (newfd);
	}
	close(newfd);
	return (fcntl(oldfd, F_DUPFD, newfd));
}
