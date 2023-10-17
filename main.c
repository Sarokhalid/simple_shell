#include "shell.h"
/**
 * main - Entry point of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 * Return: 0 on successful execution
 **/

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
		struct stat st;

		if (stat(argv[1], &st) == 0 && S_ISREG(st.st_mode))
		{
			/* If argv[1] is a file, read commands from the file */
			execute_commands_from_file(argc, argv, data);
		}
		else
		{
			/* If argv[1] is not a file, treat it as a command */
			cmd = argv[1];
			execute_cmd(cmd, argv, &data);
		}
	}
	else
	{
		/* Interactive mode: Read commands from the user */
		execute_commands_interactively(cmd, len, argv, &data);
	}

	free_commands(&data);
	clear_history(&data);
	return (0);
}
