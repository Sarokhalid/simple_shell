#include "shell.h"

int main(int argc, char *argv[])
{
	char *cmd = NULL;
	size_t len = 0;
	shell_data data;

	data.head = NULL;

	handle_signals();

	if (argc > 1)
	{
		/* Non-interactive mode: Read commands from files or pipes */
		execute_commands_from_file(argc, argv, cmd, len);
	}
	else
	{
		/* Interactive mode: Read commands from the user */
		execute_commands_interactively(cmd, len, argv, &data);
	}

	free_commands(&data);
	free(cmd); /* free the memory allocated by getline() */
	clear_history(&data);
	return (0);
}
