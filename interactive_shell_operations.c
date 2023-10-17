#include "shell.h"

void print_prompt(char *username, char *cwd)
{
	write(STDOUT_FILENO, username, _strlen(username));
	write(STDOUT_FILENO, "@", 1);
	write(STDOUT_FILENO, cwd, _strlen(cwd));
	write(STDOUT_FILENO, "$ ", 2);
}

void read_command(char **cmd, size_t *len)
{
	ssize_t read;

	read = getline(cmd, len, stdin);
	if (read == -1)
	{
		if (errno != EINVAL && isatty(STDIN_FILENO))
		{
			perror("\n");
			free(cmd);
			exit(EXIT_FAILURE);
		}
		else
		{
			exit(EXIT_SUCCESS);
		}
	}

	if ((*cmd)[read - 1] == '\n')
	{
		(*cmd)[read - 1] = '\0';
	}
}

void check_command_length(char *cmd)
{
	if (_strlen(cmd) >= MAX_CMD_LEN - 1)
	{
		const char *error_msg;

		error_msg = "Command exceeds maximum length\n";
		write(STDERR_FILENO, error_msg, _strlen(error_msg));
	}
}

void execute_commands_interactively(char *cmd, size_t len,
		char *argv[], shell_data *data)
{
	data->head = NULL;
	while (1)
	{
		char cwd[PATH_MAX];
		char *username = getenv("USER");

		if (username == NULL)
		{
			perror("Failed to get username");
			free(cmd);
			exit(EXIT_FAILURE);
		}

		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("Failed to get current directory");
			free(cmd);
			exit(EXIT_FAILURE);
		}

		if (isatty(STDIN_FILENO))
		{
			print_prompt(username, cwd);
		}

		read_command(&cmd, &len);
		handle_comments(cmd);
		if (_strlen(cmd) == 0) /* Add a check for NULL command */
		{
			continue; /* If NULL command, then continue to next iteration */
		}
		check_command_length(cmd);
		if (cmd[0] != '\0')
		{
			if (_strncmp(cmd, "exit", 4) == 0 || _strncmp(cmd, "quit", 4) == 0)
			{
				break;
			}
			handle_semicolon(cmd, argv, data);
		}
	}
	free(cmd);
}

void print_error_message(char *argv[], char *args[],
		char *error_message, int length)
{
	length += _strcpy(error_message + length, argv[0]);
	length += _strcpy(error_message + length, ": 1: ");
	length += _strcpy(error_message + length, args[0]);
	length += _strcpy(error_message + length, ": not found\n");
	write(STDERR_FILENO, error_message, length);
}