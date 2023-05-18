/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:41:55 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/07 21:41:56 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	is_tail_matched(char *file_name, char *str, char *line)
{
	char	*tail;

	if (line[ft_strlen(line) - 1] == '*')
		return (1);
	tail = ft_strchr(file_name, str[0]);
	if (tail && ft_strcmp(tail, str) == 0)
		return (1);
	return (0);
}

int	is_midlde_name_matched(char *filename, int arr_len, char **arr, char *line)
{
	int		len_to_compare;
	char	*tail;
	char	*temp;
	int		i;

	i = 0;
	len_to_compare = ft_strlen(filename) - ft_strlen(arr[arr_len - 1]);
	tail = &filename[len_to_compare];
	while (arr[i])
	{
		if (line[ft_strlen(line) - 1] != '*' && i == arr_len - 1)
			break ;
		temp = ft_strnstr(filename, arr[i], len_to_compare);
		if (temp == NULL)
			return (1);
		filename = temp + ft_strlen(arr[i]);
		i++;
	}
	return (0);
}

int	find_matching(char *file_name, char *line, char **arr, int arr_len)
{
	char	*tail;
	int		ret;
	int		i;

	i = 0;
	if (*line && arr[0] == NULL)
		return (1);
	else if (*line != '*')
	{
		if (ft_strncmp(arr[0], file_name, ft_strlen(arr[0])))
			return (0);
		file_name += ft_strlen(arr[0]);
		i += 1;
	}
	tail = &file_name[ft_strlen(file_name) - ft_strlen(arr[arr_len - 1])];
	ret = is_midlde_name_matched(file_name, arr_len, &arr[i], line);
	if (ret == 1)
		return (0);
	return (is_tail_matched(tail, arr[arr_len - 1], line));
}

int	add_filename_to_list(t_list **lst, char *line, char **arr, DIR *dir)
{
	struct dirent	*entry;
	t_list			*node;
	char			*name;

	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		name = ft_strdup(entry->d_name);
		if (name == NULL)
			return (-1);
		if (find_matching(entry->d_name, line, arr, arr_length(arr)))
		{
			node = ft_lstnew(name);
			if (node == NULL)
				return (-1);
			ft_lstadd_back(lst, node);
		}
	}
	return (0);
}

t_list	*expand_wildcard(char *line)
{
	t_list		*matches;
	t_list		*node;
	DIR			*dir;
	char		**arr;

	arr = ft_split(line, '*');
	if (!arr)
		return (NULL);
	matches = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (perror("-minishell"), free_arr(arr), NULL);
	if (add_filename_to_list(&matches, line, arr, dir) == -1)
		return (closedir(dir), ft_lstclear(&matches, free),
			free_arr(arr), NULL);
	if (!matches)
	{
		node = ft_lstnew(ft_strdup(line));
		if (node == NULL)
			return (closedir(dir), ft_lstclear(&matches, free),
				free_arr(arr), NULL);
		ft_lstadd_back(&matches, node);
		msh_err("no matches found:", line);
	}
	return (closedir(dir), free_arr(arr), matches);
}
