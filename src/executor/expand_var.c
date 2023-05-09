/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:26:18 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/03 17:48:16 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

int	is_invalid_key(const char *key)
{
	return (!(ft_isalpha(*key) || ft_strchr("$?_", *key) || ft_isdigit(*key)));
}

char	*get_key(char *str)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(*str) || *str == '_'))
		return (ft_substr(str, 0, i));
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}

int	get_expanded_length(char *str)
{
	char	*key;
	int		len;

	len = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			while (++str && *str != '\'')
				len++;
			len += 2;
		}
		if (*str == '$' && !(str[1] == 0 || is_invalid_key(str + 1)))
		{
			key = get_key(++str);
			if (!key)
				return (-1);
			str += ft_strlen(key);
			len += get_env_var_len(key);
			free(key);
		}
		else if (str++)
			len++;
	}
	return (len);
}

int	replace_var(char *expanded, char *str, int *i, int *j)
{
	char		*key;
	char		*value;

	if ((*str == 0 || is_invalid_key(str)) && ++(*j))
		*expanded = '$';
	else
	{
		key = get_key(str);
		if (!key)
			return (-1);
		value = get_env_var(key);
		if (value)
		{
			ft_memmove(expanded, value, ft_strlen(value));
			*j += ft_strlen(value);
		}
		*i += ft_strlen(key);
		return (free(key), free(value), 0);
	}
	return (0);
}

int	handle_double_quote(char *expanded, char *str, int *x, int *y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	expanded[j++] = str[i++];
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '$')
		{
			i++;
			if (replace_var(&expanded[j], &str[i], &i, &j) == -1)
				return (-1);
		}
		else
			expanded[j++] = str[i++];
	}
	if (str[i])
		expanded[j++] = str[i++];
	*x += i;
	*y += j;
	return (0);
}

void	handle_single_quote(char *expanded, char *str, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	expanded[j++] = str[i++];
	while (str[i] && str[i] != '\'')
		expanded[j++] = str[i++];
	if (str[i])
		expanded[j++] = str[i++];
	*x += i;
	*y += j;
}

char	*replace_dollar_sign(char *str, char *expanded)
{
	int		err;
	int		i;
	int		j;

	i = 0;
	j = 0;
	err = 0;
	while (str[i])
	{
		if (str[i] == '"')
			err = handle_double_quote(&expanded[j], &str[i], &i, &j);
		else if (str[i] == '\'')
			handle_single_quote(&expanded[j], &str[i], &i, &j);
		else if (str[i] == '$')
			err = replace_var(&expanded[j], &str[++i], &i, &j);
		else
			expanded[j++] = str[i++];
		if (err)
			return (free(expanded), NULL);
	}
	expanded[j] = '\0';
	return (expanded);
}

char	*modify_expanded_spaces(char *expanded)
{
	char	*modified;
	char	next_char;
	int		i;
	int		j;

	modified = malloc(ft_strlen(expanded) + 1);
	if (!modified)
		return (NULL);
	i = 0;
	j = 0;
	while (expanded[i])
	{
		if (expanded[i] == ' ' || expanded[i] == '\t')
		{
			next_char = expanded[i++];
			modified[j++] = ' ';
			while (expanded[i] == next_char)
				i++;
		}
		else
			modified[j++] = expanded[i++];
	}
	modified[j] = '\0';
	return (modified);
}

int	should_expand_var(char *str)
{
	char	next_quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			next_quote = str[i];
			i++;
			while (str[i] && str[i] != next_quote)
				i++;
			i++;
		}
		else if (str[i] == '$')
			return (1);
		else
			i++;
	}
	return (0);
}


int	add_nodes_to_expanded_list(t_list **expanded, t_list *lst)
{
	t_list	*node;
	t_list	*curr;
	char	**arr;
	int		i;

	curr = lst;
	while (lst)
	{
		if (should_expand_var(lst->content))
		{
			char *str = expand_var(lst->content);
			// str = str_expanded_spaces(lst->content);
			arr = ft_split(str, ' ');
			free(str);
			if (arr == NULL)
				return (ft_lstclear(&lst, free), -1);
			i = -1;
			while (arr[++i])
			{
				node = ft_lstnew(arr[i]);
				if (node == NULL)
					return (ft_lstclear(&lst, free), free_arr(arr), -1);
				ft_lstadd_back(expanded, node);
			}
			free(arr);
		}
		else
		{
			lst->content = remove_quotes(lst->content);
			node = ft_lstnew(ft_strdup(lst->content));
			if (node == NULL)
				return (ft_lstclear(&lst, free), -1);
			ft_lstadd_back(expanded, node);
		}
		lst = lst->next;
	}
	return (ft_lstclear(&curr, free), 0);
}

t_list	*split_expanded(t_list *lst)
{
	t_list	*expanded;
	t_list	*curr;
	t_list	*node;

	curr = lst;
	expanded = NULL;
	while (curr)
	{
		if (should_expand_var(curr->content))
		{
			node = split_content(curr->content);
			if (node == NULL)
				return (ft_lstclear(&expanded, free), NULL);
			if (add_nodes_to_expanded_list(&expanded, node) == -1)
				return (ft_lstclear(&expanded, free), ft_lstclear(&node, free), NULL);
		}
		else
		{
			curr->content = remove_quotes(curr->content);
			node = ft_lstnew(ft_strdup(lst->content));
			if (node == NULL)
				return (ft_lstclear(&expanded, free), NULL);
			ft_lstadd_back(&expanded, node);
		}
		curr = curr->next;
	}
	return (ft_lstclear(&lst, free), expanded);
}

char	*expand_var(char *str)
{
	char	*expanded;
	int		len;

	len = get_expanded_length(str);
	expanded = malloc(len + 1);
	if (expanded == NULL || len == -1)
		return (free(expanded), NULL);
	return (replace_dollar_sign(str, expanded));
}
