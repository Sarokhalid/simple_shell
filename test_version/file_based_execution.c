#include "shell.h"

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
