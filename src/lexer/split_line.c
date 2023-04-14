/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:16:08 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/13 14:13:08 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print(t_list *lst)
{
	int		i;

	if (!lst)
		return ;
	i = 1;
	printf("\n");
	while (lst)
	{
		printf("[%2d]: %s\n",i++, lst->content);
		lst = lst->next;
	}
}

t_list	*split_line(char *line)
{
	t_list	*lst;
	char	*token;
	int		error;

	error = 0;
	lst = NULL;
	while (*line)
	{
		while (*line && (*line == SPACE || *line == TAB))
			line++;
		token = get_token(line, &error);
		if (error == 1)
			return (ft_lstclear(&lst, free), NULL);
		else if (analyze_syntax(lst, token))
		{
			error = 2;
			free(token);
			break ;
		}
		if (push_token_to_list(&lst, token))
			return (ft_lstclear(&lst, free), NULL);
		line += ft_strlen(token);
	}
	if (analyse_last_node(lst, error))
		return (lst);
	return (lst);
}

