#include "shell.h"
int str_len(char *str)
{
	int k = 0;
	
	if (!str)
		return (0);
	while (*str++)
		k++;
	return (k);
}
int str_cmp(char *t1, char *t2)
{
	while (*t1 && *t2)
	{
		if (*t1 != *t2)
			return (*t1 - *t2);
		t1++;
		t2++;
	}
	if (*t1 == *t2)
		return (0);
	else
		return ((*t1 < *t2 ? -1: 1));
}
char *str_duplic(const char *str)
{
	int l = 0;
	char *r;
	
	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	for (l++; l--;)
			r[l] = *--str;
	return (r);
}
