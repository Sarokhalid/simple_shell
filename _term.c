#include "shell.h"
/**
 * _trim - Trims leading and trailing whitespace characters from a string
 * @str: The string to be trimmed.
 * Return: A pointer to the trimmed string, or NULL if str is NULL
 **/
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

/**
 * _isspace - Checks if a character is a whitespace character.
 * @c: The character to be checked.
 * Return: 1 if the character is a whitespace character, 0 otherwise.
 **/
int _isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}

/**
 * _dup2 - Duplicates a file descriptor.
 *
 * @oldfd: The original file descriptor.
 * @newfd: The new file descriptor.
 * Return: The new file descriptor on success, or -1 on error.
 */
int _dup2(int oldfd, int newfd)
{
	if (oldfd == newfd)
	{
		return (newfd);
	}
	close(newfd);
	return (fcntl(oldfd, F_DUPFD, newfd));
}
