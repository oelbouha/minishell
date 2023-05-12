
#include "../parser/parser.h"

int		main(int c, char **v, char **env)
{
	(void)c;
	(void)v;
	setup(env);
	t_list	*lst;
	t_list	*temp;
	lst = NULL;
	temp = NULL;
	set_env_var("a", "one     two");
	while (1)
	{
		char *line = readline("-> ");
		temp = tokenize(line);
		lst = split_expanded(temp);
		add_history(line);
		// if (lst)
			print(lst);
		ft_lstclear(&lst, free);
		free(line);
	}
}