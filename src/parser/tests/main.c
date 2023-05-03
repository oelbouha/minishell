

#include "parser.h"
#include <fcntl.h>

int		main(int c, char **v, char **env)
{
	(void)c;
	(void)v;
	setup(env);
	int fdin;
	int fd = open("file", O_RDONLY | O_CREAT, 0644);
	fdin = expand_heredoc(fd);
	while (1)
	{
		char *line = get_next_line(fdin);
		if (!line)
			break ;
		printf("result ===> %s\n", line);
	}
	close(fd);
	while(1)
	{
		char *line = readline("$$$:>>");
		char *expanded = expand_var(line);
		printf("result ===> %s\n", expanded);
		free(line);
		free(expanded);
	}
}