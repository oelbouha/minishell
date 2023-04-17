/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:31:32 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/17 15:10:34 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*new_heredoc_redirection(char *eof)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->type = HEREDOC;
	redir->to.heredoc.expand = TRUE;
	if (ft_strchr(eof, '"') || ft_strchr(eof, '\''))
		redir->to.heredoc.expand = FALSE;
	redir->to.heredoc.fd = read_heredoc(eof);
	return (redir);
}
