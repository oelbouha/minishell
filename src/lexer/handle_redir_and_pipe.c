/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_and_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:36:58 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/15 23:24:46 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_redir_and_pipe(char *str)
{
	char	next_char;
	int		i;

	i = 0;
	next_char = str[i];
	if (next_char == '|')
		return (1);
	if (str[i + 1] == next_char)
		i = 2;
	else
		i = 1;
	return (i);
}

int	redir_errors(t_list *lst)
{
	t_list *node;

	if (!lst)
		return (0);
	node = ft_lstlast(lst);
	if (node)
		return (ft_templatecmp(node->content, ">>:>:<<:<", ':'));
	return (1);
}

int	pipe_errors(t_list *lst)
{
	t_list *node;

	if (!lst)
		return (1);
	node = ft_lstlast(lst);
	if (node)
		return (ft_templatecmp(node->content, ">>:>:<<:<:(:):||:&&", ':'));
	return (0);
}
