#include "shell.h"

void insert_cmd(shell_data *data, const char *cmd)
{
	Node *newNode = (Node *)malloc(sizeof(Node));

	if (newNode == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	strcpy(newNode->cmd, cmd);
	newNode->next = data->head;
	data->head = newNode;

	if (HISTORY_COUNT > 0)
	{
		Node *current = data->head;
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


void clear_history(shell_data *data)
{

	while (data->head != NULL)
	{
		Node *temp = data->head;

		data->head = data->head->next;
		free(temp);
	}
}

void write_history(shell_data *data)
{
	Node *current;
	ssize_t len;
	int fd;

	/* Open the file */
	fd = open(HISTORY_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("Failed to open history file for writing");
		return;
	}

	current = data->head;
	while (current != NULL)
	{
		/* Write the command to the file */
		len = _strlen(current->cmd);
		if (write(fd, current->cmd, len) != len)
		{
			perror("Failed to write command to history file");
			close(fd);
			return;
		}

		/* Write a newline character */
		if (write(fd, "\n", 1) != 1)
		{
			perror("Failed to write newline to history file");
			close(fd);
			return;
		}

		current = current->next;
	}

	/* Close the file */
	if (close(fd) == -1)
	{
		perror("Failed to close history file");
	}
}

void read_history(shell_data *data)
{
	char cmd[MAX_CMD_LEN];
	ssize_t nread;
	int fd;

	/* Open the file */
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open history file for reading");
		return;
	}

	/* Read the commands from the file */
	while ((nread = read(fd, cmd, MAX_CMD_LEN)) > 0)
	{
		/* Remove the newline character, if present */
		if (cmd[nread - 1] == '\n')
		{
			cmd[nread - 1] = '\0';
		}
		insert_cmd(data, cmd);
	}

	/* Close the file */
	if (close(fd) == -1)
	{
		perror("Failed to close history file");
	}
}

void check_history_file(void)
{
	int fd;
	/* Open the file */
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
	{
		/* The file doesn't exist; create it */
		fd = open(HISTORY_FILE, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		if (fd == -1)
		{
			perror("Failed to create history file");
			exit(EXIT_FAILURE);
		}
	}

	/* Close the file */
	if (close(fd) == -1)
	{
		perror("Failed to close history file");
	}
}
