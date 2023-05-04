

#include "parser.h"


int	should_expand_wildcard(char *line)
{
	if (ft_templatecmp(line, "'\"/", ':'))
		return (0);
	else if (ft_strchr(line, '*'))
		return (1);
	return (0);
}

int	check_end(char *file_name, char *str)
{
	char	*end;

	end = ft_strchr(file_name, str[0]);
	if (end && ft_strcmp(end, str) == 0)
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

int	is_matched(char *file_name, char *start, char **arr)
{
	int	i;
	
	i = 0;
	if (start)
	{
		if (ft_strncmp(start, file_name, ft_strlen(start)))
			return (0);
		i += 1;
	}
	while (arr[i] && i < (get_length(arr) - 1))
	{
		if (!ft_strnstr(file_name, arr[i], ft_strlen(file_name)))
			return (0);
		i++;
	}
	if (arr[i] && !check_end(file_name, arr[i]))
		return (0);
	return (1);
}

int	add_file_name_to_list(t_list **lst, char *file_name, char *line)
{
	t_list	*node;
	char	*start;
	char	**arr;

	start = NULL;
	arr = ft_split(line, '*');
	if (!arr)
		return (-1);
	if (*line != '*')
		start = arr[0];
	if (is_matched(file_name, start, arr))
	{
		node = ft_lstnew(file_name);
		if (!node)
			return (free_arr(arr), -1);
		ft_lstadd_back(lst, node);
	}
	return (free_arr(arr), 0);
}


t_list *expand_wildcard(char *line)
{
	t_list			*lst;
    DIR				*dir;
    struct dirent 	*entry;

	lst = NULL;
    dir = opendir(".");
    if (dir == NULL)
        return  (perror("minishell: opendir failed"), NULL);
    while ((entry = readdir(dir)) != NULL)
	{
		if (add_file_name_to_list(&lst, entry->d_name, line) == -1)
			return (ft_lstclear(&lst, free), NULL);
    }
	if (!lst)
		ft_lstadd_back(&lst, ft_lstnew(line));
	return (lst);
}