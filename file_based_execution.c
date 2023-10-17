#include "shell.h"
/**
 * execute_commands_from_file - reads and executes commands
 * from one or more input files specified in the command
 * line arguments.
 *
 * @argc:   The number of command line arguments.
 * @argv:   An array of strings containing the command line arguments.
 * @data:   A data structure to manage shell-related information.
 */

void execute_commands_from_file(int argc, char *argv[], shell_data data)
{
	ssize_t nread;
	int i;
	int fd;
	char cmd[MAX_CMD_LEN];
	int index = 0;

	data.head = NULL;
	for (i = 1; i < argc; i++)
	{
		/* Open the command file */
		fd = open(argv[i], O_RDONLY);
		if (fd == -1)
		{
			perror("Failed to open command file");
			exit(EXIT_FAILURE);
		}
		/* Read commands from the file */
		while ((nread = read(fd, &cmd[index], 1)) > 0) /* Read one byte at a time */
		{
			if (cmd[index] == '\n' || index == MAX_CMD_LEN - 1)
			{
				cmd[index] = '\0'; /* Null-terminate the string */
				handle_comments(cmd);
				insert_cmd(&data, cmd);
				execute_cmd(cmd, argv, &data);
				index = 0; /* Reset index for next command */
			}
			else
			{
				index++; /* Move to next character in cmd */
			}
		}
		/* Close the command file */
		if (close(fd) == -1)
		{
			perror("Failed to close command file");
		}
		clear_history(&data);
		free_commands(&data);
	}
}
