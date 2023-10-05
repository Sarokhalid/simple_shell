#include "shell.h"
int check_delim(char j, char *str_delim)
{
	while (*str_delim)
		if (*str_delim++ == j)
			return (1);
	return (0);
}

char **str_tow(char *st, char *dilm)
{
	char **s;
	int a, b, c, f, w = 0;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!dilm)
		dilm = " ";
	for (a = 0; st[a] != '\0'; a++)
		if (!check_delim(st[a], dilm) && (check_delim(st[a + 1], dilm) || !st[a + 1]))
			w++;
	if (w == 0)
		return (NULL);
	s = malloc((1 + w) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < w; b++)
	{
		while (check_delim(st[a + c], dilm) && st[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			s[b][f] = st[a++];
		s[b][f] = 0;
	}
	s[b] = NULL;
	return (s);
}
char **str_dlm2(char *st, char dilm)
{
	char **s;
	int a, b, c, f, w = 0;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (a = 0; st[a] != '\0'; a++)
		if ((st[a] != dilm && st[a + 1] == dilm) ||
				(st[a] != dilm && !st[a + 1]) || st[a + 1] == dilm)
			w++;
	if (w == 0)
		return (NULL);
	s = malloc((1 + w) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < w; b++)
	{
		while (st[a] == dilm && st[a] != dilm)
			a++;
		c = 0;
		while (st[a + c] != dilm && st[a + c] && st[a + c] != dilm)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			s[b][f] = st[a++];
		s[b][f] = 0;
	}
	s[b] = NULL;
	return (s);
}


