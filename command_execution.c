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
	int i;

	(void)error_message;
	(void)length;
	if (_strcmp(args[0], "env") == 0)
	{
		if (args[1] != NULL && _strcmp(args[1], "-i") == 0)
		{
			/**Case: Remove all environment variables and execute env**/
			for (i = 0; environ[i] != NULL; i++)
			{
				environ[i] = NULL;
			}
		}
		execve("/usr/bin/env", args, environ);
		return;
	}
	/**Case: Execute env**/
	if (strcmp(args[0], "env") == 0)
	{
		execve("/usr/bin/env", args, environ);
		return;
	}
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
	int length = 0;
	char error_message[1024];
	pid_t pid;

	if (!command_exists(args[0]))
	{
		print_error_message(argv, args, error_message, length);
		return;
	}

	pid = fork();

	if (pid < 0)
	{
		handle_fork_error();
	}
	else if (pid == 0)
	{
		handle_child_process(args, argv, error_message, length);
	}
	else
	{
		handle_parent_process(pid);
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
void execute_cmd(char **cmd, char *argv[], shell_data *data)
{
	char *args[MAX_CMD_LEN] = {NULL};
	int i = 0;
	(void)data;

	while (cmd[i] != NULL)
	{
		args[i] = cmd[i];
		i++;
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
