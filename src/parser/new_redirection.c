/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:57:52 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/13 12:59:39 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

t_redir	*new_redirection(t_redir_type type, char *arg)
{
	t_redir	*r;

	r = ft_calloc(1, sizeof(t_redir));
	if (r == NULL)
		return (NULL);
	r->type = type;
	if (type == FILE_IN || type == FILE_OUT || type == FILE_APPEND)
		r->to.file = arg;
	return (r);
}
