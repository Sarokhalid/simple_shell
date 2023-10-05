#include "shell.h"
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
void err_msg(make_t *make, char *errty)
{
	str_input(make->pro_name);
	str_input(": ");
	base10(make->err_count, STDERR_FILENO);
	str_input(": ");
	str_input(make->arr_getline[0]);
	str_input(": ");
	str_input(errty);
}
int char_to_stdout(char j)
{
	static int o;
	static char buffer[WRITE_BUF_SIZE];
	if (j == BUF_FLUSH || o >= WRITE_BUF_SIZE)
	{
		write(1, buffer, o);
		o = 0;
	}
	if (j != BUF_FLUSH)
		buffer[o++] = j;
	return (1);
}

