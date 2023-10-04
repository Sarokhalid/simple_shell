/**#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>**/
#include "shell.h"
#include <pwd.h>

#define MAX_CMD_LEN 256
#define HISTORY_COUNT 10
#define HISTORY_FILE "history.txt"
typedef struct Node
{
	char cmd[MAX_CMD_LEN];
	struct Node *next;
} Node;

Node *head = NULL;

void handle_sigint(int signum)
{
	(void)signum;
	printf("\n$ ");
	fflush(stdout);
}

void handle_sigtstp(int signum)
{
	(void)signum;
	printf("\n");
}

void insert_cmd(const char *cmd)
{
	Node *newNode = (Node *)malloc(sizeof(Node));

	if (newNode == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	strcpy(newNode->cmd, cmd);
	newNode->next = head;
	head = newNode;

	if (HISTORY_COUNT > 0)
	{
		Node *current = head;
		Node *prev = NULL;

		int count = 0;

		while (current->next != NULL)
		{
			prev = current;
			current = current->next;
			count++;
		}

		if (count >= HISTORY_COUNT)
		{
			prev->next = NULL;
			free(current);
		}
	}
}

void clear_history(void)
{
	while (head != NULL)
	{
		Node *temp = head;
		head = head->next;
		free(temp);
	}
}

void write_history(void)
{
	Node *current;

	FILE *file = fopen(HISTORY_FILE, "w");
	if (file == NULL)
	{
		perror("Failed to open history file for writing");
		return;
	}


	current = head;
	while (current != NULL)
	{
		fprintf(file, "%s\n", current->cmd);
		current = current->next;
	}
	fclose(file);
}

void read_history(void)
{
	char cmd[MAX_CMD_LEN];

	FILE *file = fopen(HISTORY_FILE, "r");
	if (file == NULL)
	{
		perror("Failed to open history file for reading");
		return;
	}
	while (fgets(cmd, MAX_CMD_LEN, file) != NULL)
	{
		size_t len = strlen(cmd);
		if (cmd[len - 1] == '\n')
		{
			cmd[len - 1] = '\0';
		}
		insert_cmd(cmd);
	}
	fclose(file);
}

void execute_cmd(const char *cmd)
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

	/* Add cd Command - Change Directories */
	if (strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "cd: expected argument\n");
		}
		else
		{
			if (chdir(args[1]) != 0)
			{
				perror("cd");
			}
		}
	}
	else
	{
		pid_t pid = fork();
		if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execvp(args[0], args);
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			int status;
			waitpid(pid, &status, 0);
		}
	}
}


int main(void)
{
	char cmd[MAX_CMD_LEN];
	size_t len;
	FILE *checkFile;
	FILE *createFile;
			         
	signal(SIGINT, handle_sigint);
	signal(SIGTSTP, handle_sigtstp);
	checkFile = fopen(HISTORY_FILE, "r");
	if (checkFile == NULL)
	{
		/* The file doesn't exist; create it */
		createFile = fopen(HISTORY_FILE, "w");
		if (createFile == NULL)
		{
			perror("Failed to create history file");
			exit(EXIT_FAILURE);
		}
		fclose(createFile);
	}
	else
	{
		fclose(checkFile);
	}

	read_history();

	while (1)
	{
		char cwd[PATH_MAX];
		struct passwd *pw = getpwuid(getuid());
		char *username = pw->pw_name;

		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("Failed to get current directory");
			exit(EXIT_FAILURE);
		}

		printf("%s@%s:%s$ ", username, "localhost", cwd);
		fflush(stdout);

		if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
		{
			perror("Failed to read command");
			exit(EXIT_FAILURE);
		}

		len = strlen(cmd);
		if (cmd[len - 1] == '\n')
		{
			cmd[len - 1] = '\0';
		}

		if (strlen(cmd) >= MAX_CMD_LEN - 1)
		{
			printf("Command exceeds maximum length\n");
			continue;
		}
		/* Add "quit" to terminate the shell */
		if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0)
		{
			break;
		}

		insert_cmd(cmd);

		execute_cmd(cmd);
	}

	write_history();
	clear_history();
	return (0);
}
