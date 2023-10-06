#include "shell.h"
int base10(int inp, int filed)
{
	int (*__putchar)(char) = char_to_stdout;
	int y, t = 0;
	unsigned int abs, curr;

	if (filed == STDERR_FILENO)
		__putchar = char_to_stder;
	if (inp < 0)
	{
		abs = -inp;
		__putchar('-');
		t++;
	}
	else
		abs = inp;
	curr = abs;
	for (y = 1000000000; y > 1; y/= 10)
	{
		if (abs / y)
		{
			__putchar('0' + curr / y);
			t++;
		}
		curr %= y;
	}

	__putchar('0' + curr);
	t++;
	return (t);
}
