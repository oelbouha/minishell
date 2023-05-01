/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:41:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/29 12:16:47 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir_type	get_redir_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (FILE_IN);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token, ">") == 0)
		return (FILE_OUT);
	else if (ft_strcmp(token, ">>") == 0)
		return (FILE_APPEND);
	return (NOT_REDIR);
}

int	is_heredoc(t_redir *redir)
{
	return (redir->type == HEREDOC);
}

void	del_heredoc(t_redir *redir)
{
	if (redir == NULL)
		return ;
	close(redir->to.heredoc.fd);
	free(redir);
}

t_list	*get_cmd_redirs(t_list **head)
{
	t_list			*redirs;
	t_redir			*redir;
	t_list			*token;
	t_list			*prev;
	t_redir_type	type;

	token = *head;
	redirs = NULL;
	while (token)
	{
		if (is_redirection(token->content))
		{
			type = get_redir_type(token->content);
			if (type == HEREDOC)
			{
				ft_lstremove_if(&redirs, (t_lstcmp)is_heredoc, (t_lstdel)del_heredoc);
				redir = new_heredoc_redirection(token->next->content);
				free(token->next->content);
			}
			else
				redir = new_file_redirection(token->next->content, type);
			if (redir == NULL)
				return (ft_lstclear(&redirs, free), NULL);
			token->next->content = redir;
			prev = token;
			token = move_node(&redirs, token->next, prev);
			ft_lstdelone(prev, free);
			continue ;
		}
		else if (is_an_operator(token->content))
			break ;
		token = token->next;
	}
	*head = token;
	if (redirs == NULL)
		return (NO_REDIRS);
	return (redirs);
}

void	destroy_redir(t_redir *redir)
{
	if (redir)
	{
		if (redir->type == HEREDOC)
			close(redir->heredocfd);
		else
			free(redir->to.filename);
		free(redir);
	}
}
