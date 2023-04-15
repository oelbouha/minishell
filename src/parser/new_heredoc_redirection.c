/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:31:32 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/14 23:21:48 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*new_heredoc_redirection(char *eof)
{
	t_list	*heredoc_redir;
	t_redir	*redir;

	heredoc_redir = ft_calloc(1, sizeof(t_list));
	if (heredoc_redir == NULL)
		return (NULL);
	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (free(heredoc_redir), NULL);
	heredoc_redir->content = redir;
	redir->type = HEREDOC;
	redir->to.heredoc.expand = TRUE;
	if (ft_strchr(eof, '"') || ft_strchr(eof, '\''))
		redir->to.heredoc.expand = FALSE;
	redir->to.heredoc.fd = read_heredoc(eof);
	return (heredoc_redir);
}
