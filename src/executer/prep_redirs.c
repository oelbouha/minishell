/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:02:44 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/26 19:05:55 by ysalmi           ###   ########.fr       */
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

int	handle_filename_redir(t_redir *redir)
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
		return (0);
	expanded = get_expanded(redir->to.filename);
	if (expanded == NULL)
		return (1);
	else if (expanded == (t_list *)(char *)-1 || ft_lstsize(expanded) > 1)
		return (msh_log(redir->to.filename, "ambiguous redirect", 0, FALSE), 1);
	fd = open(expanded->content, oflags, 0644);
	if (fd == -1)
		return (msh_log(expanded->content, strerror(errno), NULL, FALSE), 1);
	dup2(fd, to);
	ft_lstclear(&expanded, free);
	return (close(fd), 0);
}

int	prep_redirs(t_list *redirs)
{
	t_list	*cur;

	if (redirs == (t_list *)-1)
		return (0);
	cur = redirs;
	while (cur)
	{
		handle_fd_redir(cur->content);
		if (handle_filename_redir(cur->content))
			return (1);
		cur = cur->next;
	}
	return (0);
}
