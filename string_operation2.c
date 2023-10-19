#include "shell.h"
/**
 * _strcmp - Compare two strings in a case-insensitive manner
 * @s1: The first string to compare
 * @s2: The second string to compare
 * Return: Negative value if s1 is less than s2,
 * positive value if s1 is greater than s2,
 * or 0 if s1 and s2 are equal.
 **/
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		int d = _tolower(*s1) - _tolower(*s2);

		if (d != 0)
		{
			return (d);
		}
		s1++;
		s2++;
	}
	return (_tolower(*s1) - _tolower(*s2));
}

/**
 * _tolower - Convert a character to lowercase
 * @c: The character to convert
 * Return: Lowercase version of the character if it is an uppercase letter,
 * or the character itself if it is not an uppercase letter.
 **/
int _tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c + ('a' - 'A'));
	}
	return (c);
}
