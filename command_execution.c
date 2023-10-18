#include "shell.h"
/**
 * execute_cd_command - executes the "cd" command to change directories.
 * @args: array of command arguments.
 * Description: This function handles the "cd" command, which is used to change
 * directories. If no argument is provided, an error message is printed
 * to standard error. If an argument is provided, the chdir function is called
 * to change the current directory. If chdir fails, an error message is printed
 * to standard error.
 **/

void execute_cd_command(char *args[])
{
	const char *error_msg;

	if (args[1] == NULL)
	{
		error_msg = "cd: expected argument\n";
		if (write(STDERR_FILENO, error_msg, _strlen(error_msg)) == -1)
		{
			perror("Write failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	}
}

/**
 * execute_command_in_path - Executes a command by
 * searching in the system's PATH.
 * @args: Array of command arguments.
 * @error_message: Error message buffer.
 * @length: Pointer to the length of the error message.
 * Description: This function searches for the command specified by
 * the first argument in the args array within the directories listed in the
 * system's PATH environment variable. If the command is found and
 * is executable it is executed using the execve function.
 * The error_message and length parameters are not used in this implementation.
 **/
void execute_command_in_path(char *args[], char *error_message, int *length)
{
	char *path = _getenv("PATH");
	char *dir = strtok(path, ":");
	char exec_path[MAX_CMD_LEN];

	(void)error_message;
	(void)length;

	while (dir != NULL)
	{
		_strcpy(exec_path, dir);
		_strcat(exec_path, "/");
		_strcat(exec_path, args[0]);
		if (access(exec_path, X_OK) == 0)
		{
			execve(exec_path, args, environ);
			break;
		}
		dir = strtok(NULL, ":");
	}
}

/**
 * execute_other_command - Executes a command not handled by built-in commands.
 * @args: Array of command arguments.
 * @argv: Array of command-line arguments.
 * Description: This function forks a new process and attempts to execute the
 * command specified by the first argument in the args array.
 * If the execution fails, it tries to find the command in the system's PATH
 * If the command is still not found, an error message is printed
 * The parent process waits for the childm process
 * to complete before continuing.
 **/
void execute_other_command(char *args[], char *argv[])
{
	pid_t pid = fork();
	int length = 0;
	char error_message[1024];

	if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Try to execute the command directly */
		if (execve(args[0], args, environ) == -1)
		{
			execute_command_in_path(args, error_message, &length);
			/* If we still can't execute the command, print an error message */
			print_error_message(argv, args, error_message, length);
			exit(127);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) /* If the child process exited normally*/
		{
			int child_exit_status = WEXITSTATUS(status);

			if (child_exit_status == 127)
			{
				exit(127); /* Exit the parent process with status 127 */
			}
		}
	}
}

/**
 * execute_cmd - Executes a command.
 * @cmd: Command string to be executed.
 * @argv: Array of command-line arguments.
 * @data: Pointer to the shell_data struct.
 * Description: This function tokenizes the command string into
 * individual arguments and executes the appropriate command based
 * on the first argument.
 * If the command is "cd", the execute_cd_command function is called.
 * Otherwise, the execute_other_command function is called.
 * Before executing the command, the command history is written
 * to the history file.
 **/
void execute_cmd(const char *cmd, char *argv[], shell_data *data)
{
	char *args[MAX_CMD_LEN] = {NULL};
	char *token = strtok((char *)cmd, " ");
	int i = 0;
	(void)data;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/* Add cd Command - Change Directories */
	if (args[0])
	{
		if (_strncmp(args[0], "cd", 2) == 0)
		{
			execute_cd_command(args);
		}
		else
		{
			execute_other_command(args, argv);
		}
	}
}

/**
 * free_commands - Frees the memory occupied by the command history list.
 * @data: Pointer to the shell_data struct.
 * Description: This function traverses the command history list and frees
 * the memory occupied by each node. After freeing the memory,
 * the head of the history list is set to NULL.
 **/
void free_commands(shell_data *data)
{
	Node *current = data->head;
	Node *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	data->head = NULL;
}
