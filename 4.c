#include "shell.h"
int exit_shell(make_t *make)
{
	int ech;
	if (make->argv[1])
	{
		ech = str_to_int(make->argv[1]);
		if (ech == -1)
		{
			make->status = 2;
			err_msg(make, "number isn't legal");
			str_input(make->argv[1]);
			char_to_stder('\n');
			return (1);
		}
		make->err_exit = str_to_int(make->argv[1]);
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

void str_input(char *string)
{
	int o = 0;
	
	if (!string)
		return;
	while (string[o] != '0')
	{
		char_to_stder(string[o]);
		o++;
	}
}
int char_to_stder(char j)
{
	static int o;
	static char buffer[WRITE_BUF_SIZE];
	
	if (j == BUF_FLUSH || o >= WRITE_BUF_SIZE)
	{
		write(2, buffer, o);
		o = 0;
	}
	if (j != BUF_FLUSH)
		buffer[o++] = j;
	return (1);
}
