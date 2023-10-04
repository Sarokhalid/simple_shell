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
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define MAX_CMD_LEN 256
#define HISTORY_COUNT 10
#define HISTPORY_FILE "history.txt"
#define CONVERT_LOWERCASE 1
#define CONVERT_NSIGNED 2
typedef struct Node
{
	char cmd[MAX_CMD_LEN];
	struct Node *next;
} Node;
Node *head = NULL;
typedef struct linked_list
{
	int nfield;
	char *string;
	struct linked_list *next;
} linked_t;
typedef struct passing
{
	char *arg;
	char **argv;
	char *str_path;
	int argc;
	int err_exit;
	unsigned int err_count;
	int line_flag;
	char *pro_name;
	linked_t enviro;
	linked_t his;
	linked_t *alias;
	char **modi;
	int status;
	char command_buf;
	int rfield;
	int hisc;
} make_t;
int str_to_int(char *d);
int exit_shell(make_t *make);
void str_input(char *string);
int char_to_stder(char j);
void err_msg(make_t *make, char *errty);
int base10(int inp, int filed);
int char_to_stdout(char j);
int check_alpha(int z);
int atoi_2(char *str);
int check_delim(char j, char *str_delim);
int shell_intrac(make_t *make);
/**int str_len(char *str);
int str_cmp(char *t1, char *t2);
char *starting(const char *str_sea, const char *sub_str);
char *str_conc(char *dest, char *sour);
char *str_copy(char *dest, char *sour);
char *str_duplic(const char *str);
void print_str(char *str);**/
void handle_sigint(int signum);void handle_sigint(int signum);
void handle_sigtstp(int signum);
void insert_cmd(const char *cmd);
void clear_history(void);
void write_history(void);
void read_history(void);void read_history(void);
void execute_cmd(const char *cmd);
