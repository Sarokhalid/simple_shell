#include "shell.h"
/**
 * _strlen - Calculates the length of a string.
 * @s: The string to calculate the length of.
 * Return: The length of the string.
 **/

size_t _strlen(const char *s)
{
	size_t l = 0;

	while (s[l] != '\0')
		l++;
	return (l);
}

/**
 * _strncmp - Compares two strings up to a specified number of characters.
 * @s: The first string to compare.
 * @ss: The second string to compare.
 * @n: The maximum number of characters to compare.
 * Return: An integer less than, equal to,
 * or greater than 0 if the first string is
 * less than, equal to, or greater than the second string, respectively.
 **/
int _strncmp(const char *s, const char *ss, size_t n)
{
	size_t y = 0;

	while (s && ss && y < n && s[y] != '\0' && ss[y] != '\0')
	{
		if (s[y] != ss[y])
			return (s[y] - ss[y]);
		y++;
	}
	if (y == n)
		return (0);
	return ((s && ss) ? (s[y] - ss[y]) : 0);
}

/**
 * _strcpy - Copies a string from source to destination.
 * @dest: The destination string.
 * @src: The source string.
 * Return: The length of the copied string.
 **/
size_t _strcpy(char *dest, const char *src)
{
	char *save = dest;

	while ((*dest++ = *src++))
		;
	return (dest - save - 1);
}

/**
 * _strcat - Concatenates a source string to the end of a destination string.
 * @dest: The destination string.
 * @src: The source string.
 * Return: A pointer to the resulting concatenated string.
 **/
char *_strcat(char *dest, const char *src)
{
	char *save = dest;

	while (*dest)
		dest++;
	while ((*dest++ = *src++))
		;
	return (save);
}

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @str: The string to search.
 * @c: The character to locate.
 * Return: A pointer to the first occurrence of the character in the string
 * or NULL if the character is not found.
 **
char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}**/

