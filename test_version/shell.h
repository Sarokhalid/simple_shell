#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>

#define MAX_CMD_LEN 256
#define HISTORY_COUNT 10
#define HISTORY_FILE "history.txt"

extern char **environ;

typedef struct Node
{
	char cmd[MAX_CMD_LEN];
	struct Node *next;
} Node;

typedef struct shell_data
{
	Node *head;
} shell_data;


size_t _strlen(const char *s);
int _strncmp(const char *s, const char *ss, size_t n);
void handle_sigint(int signum);
void handle_sigtstp(int signum);
void insert_cmd(shell_data *data, const char *cmd);
void clear_history(shell_data *data);
void write_history(shell_data *data);
void read_history(shell_data *data);
void execute_cd_command(char *args[]);
char *_getenv(const char *name);
size_t _strcpy(char *dest, const char *src);
void handle_signals(void);
void check_history_file(void);
void execute_cmd(const char *cmd, char *argv[], shell_data *data);
void print_prompt(char *username, char *cwd);
void check_command_length(char *cmd);
void read_command(char **cmd, size_t *len);
char *_strcat(char *dest, const char *src);
void execute_other_command(char *args[], char *argv[]);
void execute_command_in_path(char *args[],
		char *error_message, int *length);
void print_error_message(char *argv[], char *args[],
		char *error_message, int length);
void execute_commands_from_file(int argc, char *argv[],
		char *cmd, size_t len);
void execute_commands_interactively(char *cmd, size_t len,
		char *argv[], shell_data *data);


#endif /* shell.h */
