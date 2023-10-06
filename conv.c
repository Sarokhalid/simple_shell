#include "shell.h"
int check_alpha(int m)
{
	if ((m >= 'a' && m <= 'z') || (m >= 'A' && m <= 'Z'))
		return (1);
	else
		return (0);
}

int atoi_2(char *str)
{
	unsigned int res = 0;
	int q, s = 1, ou, flag = 0;

	for (q = 0; str[q] != '\0' && flag != 2; q++)
	{
		if (str[q] == '-')
			s *= -1;
		if (str[q] >= '0' && str[q] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (str[q] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (s == -1)
		ou = -res;
	else
		ou = res;
	return (ou);
}
