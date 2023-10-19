#include "shell.h"
/**
 * print_prompt - Prints the shell prompt.
 * Description: This function prints the shell prompt to standard output
 * the current working directory, and a "$ " symbol indicating
 * are pointers to null-terminated strings.
 **/

void print_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * read_command - Reads a command from stdin.
 * @cmd: Pointer to the command buffer.
 * @len: Pointer to the length of the command buffer.
 * Description: This function reads a command from standard input using
 * the getline function. It stores the command in the cmd buffer and updates
 * the len parameter with the length of the command.
 * If an error occurs or the command is empty, the function exits the program.
 * If the command ends with a newline character, it is replaced with
 * a null terminator.
 **/
void read_command(char **cmd, size_t *len)
{
	ssize_t read;

	read = getline(cmd, len, stdin);
	if (read == -1)
	{
		if (errno == EINVAL)  /* Some other error occurred */
		{
			write(STDOUT_FILENO, "\n", 1);
			free(*cmd);
			*cmd = NULL;
			exit(EXIT_FAILURE);
		}
		else  /* User pressed Ctrl+D */
		{
			free(*cmd);
			*cmd = NULL;
			exit(EXIT_SUCCESS);
		}
	}

	if ((*cmd)[read - 1] == '\n')
	{
		(*cmd)[read - 1] = '\0';
	}
}

/**
 * check_command_length - Checks if a command exceeds the maximum length.
 * @cmd: Pointer to the command string.
 * Description: This function checks if the length of the command exceeds the
 * maximum allowed length defined by MAX_CMD_LEN. If the command exceeds the
 * maximum length, an error message is printed to the standard error output.
 **/
void check_command_length(char *cmd)
{
	if (_strlen(cmd) >= MAX_CMD_LEN - 1)
	{
		const char *error_msg;

		error_msg = "Command exceeds maximum length\n";
		write(STDERR_FILENO, error_msg, _strlen(error_msg));
	}
}

/**
 * execute_commands_interactively - Executes commands interactively in a shell.
 * @cmd: Pointer to the command buffer.
 * @len: Length of the command buffer.
 * @argv: Array of command-line arguments.
 * @data: Pointer to shell data structure.
 * Description: This function executes commands interactively in a shell. It
 * repeatedly prompts for input, reads the command, handles comments
 * checks for the exit or quit commands, and handles commands separated
 * by semicolons.
 **/
void execute_commands_interactively(char *cmd, size_t len,
		char *argv[], shell_data *data)
{
	data->head = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			print_prompt();
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
				free(cmd);
				break;
			}
			handle_semicolon(cmd, argv, data);
		}
	}
}

/**
 * print_error_message - Prints an error message to standard error.
 * @argv: Array of command-line arguments.
 * @args: Array of command arguments.
 * @error_message: Error message buffer.
 * @length: Length of the error message.
 * Description: This function constructs an error message and prints it to
 * standard error. The error message includes the program name,the command name
 * and an error message indicating that the command was not found
 * The length parameter is used to keep track of the length of the
 * error message.
 **/
void print_error_message(char *argv[], char *args[],
		char *error_message, int length)
{
	length += _strcpy(error_message + length, argv[0]);
	length += _strcpy(error_message + length, ": 1: ");
	length += _strcpy(error_message + length, args[0]);
	length += _strcpy(error_message + length, ": not found\n");
	write(STDERR_FILENO, error_message, length);
}
