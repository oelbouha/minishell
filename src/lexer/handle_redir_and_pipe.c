/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_and_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:36:58 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/07 21:37:18 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_redir_and_pipe(t_list **lst, char *str, int *err)
{
	char	*token;
	char	next_char;
	int		i;

	i = 0;
	next_char = str[i];
	if (str[i + 1] == next_char)
		i = 2;
	else
		i = 1;
	token = ft_substr(str, 0, i);
	if (!token)
	{
		*err = 1;
		return (1);
	}
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i);
}
