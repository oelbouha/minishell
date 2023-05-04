/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:41:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/04 17:41:22 by ysalmi           ###   ########.fr       */
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

t_list	*get_cmd_redirs(t_list **head)
{
	t_list		*redirs;
	t_list		*token;

	token = *head;
	redirs = NULL;
	while (token)
	{
		if (is_redirection(token->content))
		{
			if (add_redirection(&redirs, &token))
				return (ft_lstclear(&redirs, free), NULL);
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

int	add_redirection(t_list **redirs, t_list **head)
{
	t_list			*token;
	t_list			*redir_node;
	t_redir			*redir;
	t_redir_type	type;

	token = *head;
	redir_node = token->next;
	type = get_redir_type(token->content);
	if (type == HEREDOC)
	{
		ft_lstremove_if(redirs, (t_lstcmp)is_heredoc, (t_lstdel)del_heredoc);
		redir = new_heredoc_redirection(redir_node->content);
		if (redir)
			free(redir_node->content);
	}
	else
		redir = new_file_redirection(redir_node->content, type);
	if (redir == NULL)
		return (1);
	redir_node->content = redir;
	*head = move_node(redirs, redir_node, token);
	ft_lstdelone(token, free);
	return (0);
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
