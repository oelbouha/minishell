/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_file_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:15:39 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/13 17:25:12 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

t_list	*new_file_redirection(char *filename, t_redir_type type)
{
	t_list	*file_redir;
	t_redir	*redir;

	file_redir = ft_calloc(1, sizeof(t_list));
	if (file_redir == NULL)
		return (NULL);
	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (free(file_redir), NULL);
	file_redir->content = redir;
	redir->type = type;
	redir->to.filename = filename;
	return (file_redir);
}
