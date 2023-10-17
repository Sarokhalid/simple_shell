#include "shell.h"
/**
 * execute_commands_from_file - Executes commands from a file in the shell.
 * @argc: The number of command line arguments.
 * @argv: An array of strings containing command line arguments.
 * @cmd: The buffer for storing commands read from the file.
 * @len: The length of the buffer (unused).
 * Description: This function reads commands from a filespecified
 * by command line arguments and executes them in the shell.
 * It opens each command file ,reads commands from it, inserts the commands
 * into the shell_data struct using insert_cmd, and executes them
 * using the execute_cmd function. After processing all commands
 * the command file is closed, and the command history
 * and allocated memory are cleared.
 * The (void)len is used to explicitly indicate ,that the len parameter
 * is unused to avoid a warning about an unused variable.
 **/

void execute_commands_from_file(int argc, char *argv[], char *cmd, size_t len)
{
	ssize_t nread;
	int i;
	int fd;
	shell_data data;
	(void)len;

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
		while ((nread = read(fd, cmd, MAX_CMD_LEN)) > 0)
		{
			if (_strlen(cmd) == 0) /* If NULL command, exit the shell */
			{
				exit(EXIT_SUCCESS);
			}
			if (cmd[nread - 1] == '\n')
			{
				cmd[nread - 1] = '\0';
			}

			insert_cmd(&data, cmd);
			execute_cmd(cmd, argv, &data);
		}
		/* Close the command file */
		if (close(fd) == -1)
		{
			perror("Failed to close command file");
		}
		clear_history(&data);
		free_commands(&data);
		free(cmd);
	}
}
