/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:02:44 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 20:37:34 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	handle_fd_redir(t_redir *redir)
{
	int	to;

	if (redir->type == HEREDOC 
		|| redir->type == PIPE_IN
		|| redir->type == PIPE_OUT)
	{
		if (redir->type == HEREDOC && redir->to.fd.expand == TRUE)
			redir->to.fd.val = expand_heredoc(redir->to.fd.val);
		to = (redir->type == PIPE_OUT);
		dup2(redir->to.fd.val, to);
		close(redir->to.fd.val);
	}
	else if (redir->type == PIPE_UNUSED)
		close(redir->to.fd.val);
}

void	handle_filename_redir(t_redir *redir)
{
	t_list	*expanded;
	int		fd;
	int		to;
	int		oflags;

	to = 0;
	if (redir->type == FILE_IN)
		oflags = O_RDONLY;
	else if (redir->type == FILE_OUT && ++to)
		oflags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redir->type == FILE_APPEND && ++to)
		oflags = O_WRONLY | O_CREAT | O_APPEND;
	else
		return ;
	expanded = get_expanded(redir->to.filename);
	if (expanded == NULL)
		exit(1);
	else if (expanded == (t_list *)EMPTY_VAR || ft_lstsize(expanded) > 1)
	{
		msh_log(redir->to.filename, "ambiguous redirect", NULL, FALSE);
		exit(1);
	}
	fd = open(expanded->content, oflags, 0644);
	if (fd == -1)
	{
		msh_log(expanded->content, strerror(errno), NULL, FALSE);
		exit(1);
	}
	dup2(fd, to);
	close(fd);
	ft_lstclear(&expanded, free);
}

int	prep_redirs(t_list *redirs)
{
	t_list	*cur;

	if (redirs == NO_REDIRS)
		return (0);
	cur = redirs;
	while (cur)
	{
		handle_fd_redir(cur->content);
		handle_filename_redir(cur->content);
		cur = cur->next;
	}
	return (0);
}
