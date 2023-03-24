#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <curses.h>
#include <term.h>


void	rl_replace_line(const char *text, int a);

int	custom(const char *s, int n)
{
	printf("starting...\n");
	printf("s: %s, n: %d\n", s, n);
	return 0;
}

int main()
{
	char buff[2048];
	char *type = getenv("TERM");
	int success;
	success = tgetent(buff, type);
	printf("%d |%s|\n", success, buff);

	char 	*in;
	rl_startup_hook = custom;
	while (1)
	{
		in = readline("-> ");
		if (in != NULL || *in != 0)
			add_history(in);
		puts(in);
		puts(rl_terminal_name);
		free(in);
	}
	return (0);
}
