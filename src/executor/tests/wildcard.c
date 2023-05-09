

#include "../parser/parser.h"

int		main(int c, char **v, char **env)
{
	(void)c;
	(void)v;
	t_list	*lst;
	t_list	*temp;
	setup(env);
	lst = NULL;
	set_env_var("a", "hello    'fff       fff'     world");
	while (1)
	{
		char *line = readline("$$$: ");
		// if (should_expand_var(line))
		// 	printf("expand %s\n", expand_var(line));
		temp = split_line(line);
		lst = split_expanded(temp);
		add_history(line);
		print(lst);
		ft_lstclear(&lst, free);
		free(line);
	}
}