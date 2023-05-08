

#include "../parser/parser.h"

int		main(int c, char **v, char **env)
{
	(void)c;
	(void)v;
	setup(env);
	while (1)
	{
		// char *line = readline("$$: ");
		// // lst = split_line(line);
		// if (should_expand_wildcard(line))
		// 	lst = expand_wildcard(line);
		// print(lst);
		// ft_lstclear(&lst, free);
		// free(line);
		char *line = readline("$$$: ");
		char *expanded = expand_var(line);
		add_history(line);
			printf("result:   %s\n", expanded);
		free(line);
		free(expanded);
	}
}