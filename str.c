#include "shell.h"
char *starting(const char *str_sea, const char *sub_str)
{
	while (*sub_str)
	
		if (*sub_str++ != *str_sea++)
			return (NULL);
	return ((char *)str_sea);
}

char *str_conc(char *dest, char *sour)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*sour)
		*dest++ = *sour++;
	*dest = *sour;
	return (r);
}
char *str_copy(char *dest, char *sour)
{
	int k = 0;

	if (dest == sour || sour == 0)
		return (dest);
	while (sour[k])
	{
		dest[k] = sour[k];
		k++;
	}
	dest[k] = 0;
	return (dest);
}

void print_str(char *str)
{
	int p = 0;

	if (!str)
		return;
	while (str[p] != '\0')
	{
		char_to_stdout(str[p]);
		p++;
	}
}

