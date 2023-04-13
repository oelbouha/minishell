/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:31:32 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/12 23:34:51 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_heredoc	*new_heredoc_redirection(char *arg)
{
	t_heredoc	*redir;
	char		*limiter;
	char		line[512];
	int			fds[2];

	redir = malloc(sizeof(t_heredoc));
	if (redir == NULL)
		return (NULL);
	limiter = remove_quotes(arg);
	if (pipe(fds))
		return (/*log*/free(redir), NULL);
	redir->fd = fds[0];
	while (1)
	{
		read(0, line, 256);
	}
}
