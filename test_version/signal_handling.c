#include "shell.h"

void handle_sigint(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n$ ", 4);
	fflush(stdout);
}

void handle_sigtstp(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 2);
}

void handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGTSTP, handle_sigtstp);
}
