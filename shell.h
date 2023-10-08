#define SHELL_H
#define SHELL_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define MAX_CMD_LEN 256
#define HISTORY_COUNT 10
#define HISTPORY_FILE "history.txt"
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define MAX_TOKENS 64
#define TOKEN_DELIMITERS " \t\n"
typedef struct Node
{
	char cmd[MAX_CMD_LEN];
	struct Node *next;
} Node;

void print_str(char *str);
void handle_sigint(int signum);void handle_sigint(int signum);
void handle_sigtstp(int signum);
void insert_cmd(const char *cmd);
void clear_history(void);
void write_history(void);
void read_history(void);
void execute_cmd(const char *cmd);
char **str_dlm2(char *st, char dilm);
char **str_tow(char *st, char *dilm);
char *rea(char *p, size_t s);
char *get();
void cus_exit(char *st);
int  _atoi(const char *s);
char *rea(char *p, size_t s);
int  _strncmp(const char *s, const char *d, size_t f);
char _getenv(const char *name);
void ex_comm(const char *comm);
void sep(const char *c);
