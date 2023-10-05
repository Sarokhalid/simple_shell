#include "shell.h"
int exit_shell(make_t *make)
{
	int ech;
	if (make->arr_getline[1])
	{
		ech = str_to_int(make->arr_getline[1]);
		if (ech == -1)
		{
			make->status = 2;
			err_msg(make, "number isn't legal");
			str_input(make->arr_getline[1]);
			char_to_stder('\n');
			return (1);
		}
		make->err_exit = str_to_int(make->arr_getline[1]);
		return (-2);
	}
	make->err_exit = -1;
	return (-2);
}

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
		}																		                        if (res > INT_MAX)																                                return (-1);
		else
			return (-1);
	}
	return (res);
}

