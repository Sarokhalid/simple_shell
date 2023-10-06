#include "shell.h"
char *rea(char *p, size_t s)
{
	size_t e ;
	char *v;

	if (p == NULL)
		return (malloc(s));
	v = malloc(s);
	if (v == NULL)
		return (NULL);
	for (e = 0; e < s; e++)
		v[e] = p[e];
	free(p);
	return (v);
}

char *get()
{
	char n;
	int li = 0;
	char *l;
	static int cbuff = 0;
	int ls = BUFFER_SIZE;
	static char buff[BUFFER_SIZE];
	static int ibuff = 0;

	l = malloc(BUFFER_SIZE);
	while (1)
	{
		if (ibuff >= cbuff)
		{
			cbuff = read(STDIN_FILENO, buff, BUFFER_SIZE);
			ibuff = 0;
			if (cbuff == 0)
			{
				break;
			}
		}
		n = buff[ibuff++];
		if (n == '\n')
			break;
		l[li++] = n;
		if (li >= ls)
		{
			ls += BUFFER_SIZE;
			l = rea(l, ls);
		}
	}
	l[li] = '\0';
	return (l);
}


