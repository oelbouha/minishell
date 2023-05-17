

#include "executer.h"

char	**convert_lst_to_array(t_list *lst)
{
	t_list	*temp;
	char	**arr;
	int		size;
	int		i;

	size = ft_lstsize(lst);
	arr = ft_calloc(size + 1, sizeof(char *));
	if (arr == NULL)
		return (ft_lstclear(&lst, free), NULL);
	i = -1;
	while (++i < size)
	{
		temp = lst;
		arr[i] = lst->content;
		lst = lst->next;
		free(temp);
	}
	return (arr);
}