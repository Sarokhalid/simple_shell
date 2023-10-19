#include "shell.h"
/**
 * handle_semicolon - Handles commands separated by
 * semicolons in a command string.
 * @cmd: The command string to be processed.
 * @argv: An array of strings containing command line arguments.
 * @data: Pointer to the shell_data struct containing shell information.
 * Description: This function handles commands separated
 * by semicolons in a command string It splits the command string
 * into individual commands using the semicolon as a delimiter.
 * Each command is trimmed to remove leading and trailing
 * whitespace before being processed.
 * The trimmed command is then inserted into the shell_data struct
 * using the insert_cmd function and executed
 * using the execute_cmd function.
 **/
void handle_semicolon(char *cmd, char *argv[], shell_data *data)
{
	char *token_s = cmd;
	char *token_e = cmd;
	char *trim_cmd;

	while (*token_e != '\0')
	{
		if (*token_e == ';')
		{
			*token_e = '\0';
			trim_cmd = _trim(token_s);
			if (trim_cmd[0] != '\0')
			{
				split_and_execute_cmd(trim_cmd, argv, data);
			}
			token_s = token_e + 1;
		}
		token_e++;
	}
	trim_cmd = _trim(token_s);
	if (trim_cmd[0] != '\0')
	{
		split_and_execute_cmd(trim_cmd, argv, data);
	}
}

/**
 * split_and_execute_cmd - Splits a command into arguments and executes it.
 * @trim_cmd: The command to split and execute.
 * @argv: The arguments that were passed to the program.
 * @data: The shell data structure.
 *
 * Return: void
 */
void split_and_execute_cmd(char *trim_cmd, char *argv[], shell_data *data)
{
	char *args[MAX_CMD_LEN] = {NULL};
	int arg_count = 0;
	char *token;

	/* Split trim_cmd into arguments */
	token = strtok(trim_cmd, " ");
	while (token != NULL)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;
	execute_cmd(args, argv, data);
}
