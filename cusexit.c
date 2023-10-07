#include "shell.h"
int  _atoi(const char *st)
{
	int y = 0;
	int r = 0;
	int s = 1;

	if (st[0] == '-')
	{
		s = -1;
		y++;
	}
	else if (st[0] == '+')
		y++;
	for (; st[y] != '\0'; y++)
	{
		if (st[y] >= '0' && st[y] <= '9')
			r = r * 10 + (st[y] - '0');
		else
			break;
	}
	return (r *s);
}
void cus_exit(char *st)
{
	int es = _atoi(st);
	exit(es);
}
