#include "shell.h"
/**
 * print_string - Prints a null-terminated string to the standard output
 * @string: The string to be printed
 * Description:
 * This function prints each character of the given string until it reaches
 * the null terminator '\0'. It assumes that a valid null-terminated string
 * is passed as an argument.
 **/
void print_string(const char *string)
{
	int k;

	for (k = 0; string[k] != '\0'; k++)
	{
		_putchar(string[k]);
	}
}

/**
 * _putchar - Writes a character to the standard output
 * @c: The character to be written
 * Description:
 * This function writes a single character to the standard output
 * using the write system call.
 * It assumes that the character is a valid ASCII value
 * and that the standard output is a valid file descriptor.
 **/
void _putchar(int c)
{
	char m = (char)c;

	write(STDOUT_FILENO, &m, 1);
}

/**
 * _strcmp - Compares two strings
 * @s1: The first string to be compared
 * @s2: The second string to be compared
 * Return: An integer less than, equal to, or greater than
 * zero if the first
 * string is found to be less than, equal to, or greater than the second
 * string respectively.
 * Description:
 * This function compares the strings `s1` and `s2` character by character
 * until a difference is found or the end of either string is reached. It
 * returns a value less than, equal to, or greater than zero depending on
 * whether `s1` is found to be less than, equal to, or greater than `s2`.
 **/
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
