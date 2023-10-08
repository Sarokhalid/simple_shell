#include "shell.h"
#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100
void sep(const char *c)
{
	int st;
	pid_t p;

	int ac = 0;
	char *a[MAX_COMMAND_LENGTH];
	char *t;

	t = strtok((char *)c, " ");
	while (t != NULL)
	{
		a[ac++] = t;
		t = strtok(NULL, " ");
	}
	a[ac] = NULL;
	p = fork();
	if (p == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (p == 0)
	{
		execvp(a[0], a);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(p, &st, 0);
}


