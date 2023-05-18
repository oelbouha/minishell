

#include "executer.h"

char	**convert_lst_to_array(t_list *lst)
{
	char	**arr;
	int		size;
	int		i;

	size = ft_lstsize(lst);
	arr = ft_calloc(size + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		arr[i] = lst->content;
		lst = lst->next;
	}
	return (arr);
}
