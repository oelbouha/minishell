/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:16:08 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/08 14:07:02 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print(t_list *lst)
{
	t_list *temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		printf("token ===> %s\n",temp->content);
		temp =temp->next;
	}
}

int	handle_parenthesis(t_list **lst, char *str, int *err)
{
	char	*token;

	token = ft_substr(str, 0, 1);
	if (!token)
	{
		*err = 1;
		return (1);
	}
	ft_lstadd_back(lst, ft_lstnew(token));
	return (1);
}

int	and_or_handler(t_list **lst, char *str, int *err)
{
	char	*token;

	token = ft_substr(str, 0, 2);
	if (!token)
	{
		*err = 1;
		return (1);
	}
	ft_lstadd_back(lst, ft_lstnew(token));
	return (2);
}


t_list	*split_line(char *line)
{
	t_list	*lst;
	int		error;
	int		i;

	lst = NULL;
	error = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == SPACE || line[i] == TAB)
			i++;
		else if (BONUS
			&& (!ft_strncmp(&line[i], "||", 2) || !ft_strncmp(&line[i], "&&", 2)))
			i += and_or_handler(&lst, &line[i], &error);
		else if (BONUS && (line[i] == '(' || line[i] == ')'))
			i += handle_parenthesis(&lst, &line[i], &error);
		else if (line[i] == SINGLE_QUOTE || line[i] == DOUBLE_QUOTE)
			i += handle_quotes(&lst, &line[i], &error);
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			i += handle_redir_and_pipe(&lst, &line[i], &error);
		else
			i += simple_word(&lst, &line[i], &error);
		if (error == 1)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
	}
	return (lst);
}

