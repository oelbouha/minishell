/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:26:18 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/09 15:30:51 by ysalmi           ###   ########.fr       */
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



/*
	PREP_ARGS; CHAR **
	while (arg)
	{
		if (should_expand)
			expand(&arg);
		else
			remove quotes;
		next;
	}
	args = ft_lst_to_array(lst);

	EXPAND( ARG )
	t_list *lst;
	lst = split(*arg->content);
	lst = expand_and_join(lst);
	temp = *arg->next;
	*arg = lst;
	lst = ft_lstlast(lst);
	lst->next = temp;

	
	EXPAND_AND_JOIN
	{//if needs spliting	
		expand;
		if (*expnaded == 0)
		{
			temp = cur;
			cur = cur->next;
			prev->next = cur;
			ft_lstdelone(temp, free);
			continue ;
		}
		newlst = split;
		join newlst with prev
		last = ft_lstlast(newlst);
		last->next = cur->next;
		prev->next = newlst->next;
		ft_lstdelone(cur, free);
		ft_lstdelone(newlst, free);
		cur = last->next;
	}
	{else
		remove quotes;
		expand_vars;
		join with prev if there is a prev node;prev->content = join
		prev->next = cur->next;
		ft_lstdelone(cur, free);
		cur = prev->next;
	}
*/


/*


	fdfdfd f d fd f d 
	join node 1;
	prev point to last node

*/


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
