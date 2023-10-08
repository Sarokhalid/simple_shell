#include "shell.h"
char *rep(char *c)
{
	char *rc;
	char *t;
	char *v;
	char *val;

	rc = malloc(_strlen(c) * sizeof(char));
	t = strtok(c, " ");
	while (t != NULL)
	{
		if (t[0] == '$')
		{
			v = t + 1;
			val = _getenv(v);
			if (val != NULL)
				strcat(rc, val);
		}
		else
			strcat(rc, t);
		strcat(rc, " ");
		t = strtok(NULL, " ");
	}
	return (rc);
}
			


