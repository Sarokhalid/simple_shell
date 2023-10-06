#include "shell.h"
int str_to_int(char *d)
{
	int m = 0;
	unsigned long int res = 0;

	if (*d == '+')
		d++;
	for (m = 0; d[m] != '\0'; m++)
	{
		if (d[m] >= '0' && d[m] <= '9')
		{
			res *= 10;
			res += (d[m] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**linked_t *node_prefix(linked_t *p_head, char *mat, char nch)
{
	char *a = NULL;

	while (p_head)
	{
		a = starting(p_head->str, mat);
		if (a && ((nch == -1) || (*a == nch)))
			return (p_head);
		p_head = p_head->nch;
	}
	return (NULL);
}*:x

