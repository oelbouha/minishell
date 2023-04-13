#include "lexer.h"

int	main(int c, char **v, char **e)
{
	(void)c;
	(void)v;
	setup(e);
	while (1)
	{
		char *line = read_line(1);
		ft_printf("line: [%s]\n", line);
		set_last_status(get_last_status()?0:1);
		free(line);
	}
	return (0);
}
