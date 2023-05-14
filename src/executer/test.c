
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
		lst = get_expanded(temp);
		add_history(line);
		// print(lst);
		char **arr = convert_list_to_array(lst);
		if (arr)
		{
			for (int i = 0; arr[i]; i++)
			printf("arr[%d]: %s\n", i, arr[i]);
		}
		free_arr(arr);
		free(line);
	}
}