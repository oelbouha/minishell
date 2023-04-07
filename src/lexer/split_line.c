/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:16:08 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/07 17:16:18 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	simple_word(t_list **lst, char *str, int *err)
{
	char	*token;
	int		i;

	i = word_len(str);
	token = ft_substr(str, 0, i);
	if (!token)
		*err = 1;
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i);
}

void	print(t_list *lst)
{
	t_list *temp;

	temp = lst;
	while (temp)
	{
		printf("token ===> %s\n",temp->content);
		temp =temp->next;
	}
}

t_list	*split_line(char *line)
{
	t_list	*lst;
	int		error;
	int		i;

	i = 0;
	error = 0;
	while (line[i])
	{
		if (line[i] == SPACE || line[i] == TAB)
			i++;
		else if (line[i] == SINGLE_QUOTE || line[i] == DOUBLE_QUOTE)
			i += handle_quotes(&lst, &line[i], &error);
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			i += handle_redir_and_pipe(&lst, &line[i], &error);
		else
			i += simple_word(&lst, &line[i], &error);
	}
	print(lst);
	return (lst);
}

