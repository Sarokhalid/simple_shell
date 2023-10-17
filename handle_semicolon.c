#include "shell.h"
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
				insert_cmd(data, trim_cmd);
				execute_cmd(trim_cmd, argv, data);
			}
			token_s = token_e + 1;
		}
		token_e++;
	}
	trim_cmd = _trim(token_s);
	if (trim_cmd[0] != '\0')
	{
		insert_cmd(data, trim_cmd);
		execute_cmd(trim_cmd, argv, data);
	}
}
