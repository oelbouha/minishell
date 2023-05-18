/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:02:44 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/16 20:18:50 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	prep_redirs(t_list *redirs)
{
	t_list	*cur;
	t_redir	*redir;
	int		to;
	int		fd;

	if (redirs == NO_REDIRS)
		return (0);
	cur = redirs;
	while (cur)
	{
		redir = cur->content;
		if (redir->type == HEREDOC || redir->type == PIPE_IN || redir->type == PIPE_OUT)
		{
			to = (redir->type == PIPE_OUT);
			fd = redir->to.fd.val;
			dup2(fd, to);
			close(fd);
		}
		else if (redir->type == PIPE_UNUSED)
			close(redir->to.fd.val);
		cur = cur->next;
	}
	return (0);
}
