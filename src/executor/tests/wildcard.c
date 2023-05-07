

#include "../parser/parser.h"

int		main()
{
	t_list *lst;

	lst = NULL;
	while (1)
	{
		char *line = readline("$$: ");
		// lst = split_line(line);
		if (should_expand_wildcard(line))
			lst = expand_wildcard(line);
		add_history(line);
		print(lst);
		free(line);
	}
}