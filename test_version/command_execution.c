#include "shell.h"

void execute_cd_command(char *args[])
{
	const char *error_msg;

	if (args[1] == NULL)
	{
		error_msg = "cd: expected argument\n";
		write(STDERR_FILENO, error_msg, strlen(error_msg));
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	}
}

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
		dup2(STDOUT_FILENO, 1);
		/* Try to execute the command directly */
		if (execve(args[0], args, environ) == -1)
		{
			execute_command_in_path(args, error_message, &length);
			/* If we still can't execute the command, print an error message */
			print_error_message(argv, args, error_message, length);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}

void execute_cmd(const char *cmd, char *argv[], shell_data *data)
{
	char *args[MAX_CMD_LEN];
	char *token = strtok((char *)cmd, " ");
	int i = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	write_history(data);

	/* Add cd Command - Change Directories */
	if (_strncmp(args[0], "cd", 2) == 0)
	{
		execute_cd_command(args);
	}
	else
	{
		execute_other_command(args, argv);
	}
}

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
