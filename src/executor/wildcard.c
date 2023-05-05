

#include "../parser/parser.h"

void	free_lst(t_list *lst)
{
	t_list	*curr;

	while (lst)
	{
		curr = lst;
		lst = lst->next;
		free(curr);
	}
}

int	should_expand_wildcard(char *line)
{
	if (ft_templatecmp(line, "'\"/", ':'))
		return (0);
	else if (ft_strchr(line, '*'))
		return (1);
	return (0);
}

int	is_tail_matched(char *file_name, char *str)
{
	char	*tail;

	if (!str)
		return (0);
	tail = ft_strchr(file_name, str[0]);
	if (tail && ft_strcmp(tail, str) == 0)
		return (1);
	return (0);	
}

int	get_length(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

int	is_matched(char *file_name, char *head, char **arr)
{
	int		len_to_compare;
	char	*tail;
	int		len;
	int		i;
	
	i = 0;
	len = get_length(arr) - 1;
	if (head)
	{
		if (ft_strncmp(head, file_name, ft_strlen(head)))
			return (0);
		file_name += ft_strlen(head);
		i += 1;
	}
	len_to_compare = ft_strlen(file_name) - ft_strlen(arr[len]);
	tail = &file_name[ft_strlen(file_name) - ft_strlen(arr[len])];
	while (arr[i] && i < len)
	{
		if (ft_strnstr(file_name, arr[i], len_to_compare))
			file_name += ft_strlen(arr[i]);
		else
			return (0);
		i++;
	}
	return (is_tail_matched(tail, arr[i]));
}

int	add_file_name_to_list(t_list **lst, char *file_name, char *line)
{
	t_list	*node;
	char	*head;
	char	**arr;

	head = NULL;
	arr = ft_split(line, '*');
	if (!arr)
		return (-1);
	if (*line != '*')
		head = arr[0];
	if (is_matched(file_name, head, arr))
	{
		node = ft_lstnew(file_name);
		if (node == NULL)
			return (free_arr(arr), -1);
		ft_lstadd_back(lst, node);
	}
	return (free_arr(arr), 0);
}


t_list *expand_wildcard(char *line)
{
    struct dirent 	*entry;
	t_list			*lst;
	t_list			*node;
    DIR				*dir;

	lst = NULL;
    dir = opendir(".");
    if (dir == NULL)
        return  (perror("-minishell"), NULL);
    while ((entry = readdir(dir)) != NULL)
	{
		if (add_file_name_to_list(&lst, entry->d_name, line) == -1)
			return (closedir(dir), free_lst(lst), NULL);
    }
	if (!lst)
	{
		node = ft_lstnew(line);
		if (node == NULL)
			return (closedir(dir), free_lst(lst), NULL);
		ft_lstadd_back(&lst, node);
		msh_err("no matches found:", line);
	}
	return (closedir(dir), lst);
}