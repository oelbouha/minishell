/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:16:08 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/16 18:10:07 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*split_line(char *line)
{
	t_list	*lst;
	char	*token;
	int		error;
	int		*err;

	err = &error;
	error = 0;
	lst = NULL;
	while (*line)
	{
		while (*line && (*line == SPACE || *line == TAB))
			line++;
		token = get_token(line, err);
		if (*err == 1)
			return (ft_lstclear(&lst, free), NULL);
		else if (analyze_syntax(lst, token))
		{
			*err = 2;
			free(token);
			break ;
		}
		if (push_token_to_list(&lst, token))
			return (ft_lstclear(&lst, free), NULL);
		if (*err == 3)
			break ;
		line += ft_strlen(token);
	}
	if (analyse_last_node(lst, *err))
		return (lst);
	return (lst);
}
