/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:41:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/17 16:46:25 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_minishell_operator(char *token)
{
	int	ret;

	ret = (ft_templatecmp(token, "|:>:>>:<:<<", ':')
		|| (BONUS && ft_templatecmp(token, "(:):||:&&", ':')));
	return (ret);
}

int	is_redirection(char *token)
{
	return (ft_templatecmp(token, ">:>>:<:<<", ':'));
}

int	get_cmd_args_count(t_list *start)
{
	int	count;

	count = 0;
	while (start)
	{
		if (is_redirection(start->content))
			start = start->next;
		else if (is_minishell_operator(start->content))
			break ;
		else
			count++;
		start = start->next;
	}
	return (count);
}

//move node moves a node from a linked list to another and
//returns the node next to the node moved.
t_list	*move_node(t_list *prev, t_list *node, t_list **to)
{
	t_list	*temp;

	if (prev)
		prev->next = node->next;
	else
		temp = node->next;
	node->next = NULL;
	ft_lstadd_back(to, node);
	if (prev)
		return (prev->next);
	return (temp);
}

t_list	*get_cmd_args_list(t_list **head, int count)
{
	t_list	*args;
	t_list	*start;
	t_list	*prev;

	args = NULL;
	prev = NULL;
	start = *head;
	while (start && count > 0)
	{
		if (is_redirection(start->content))
		{
			if (prev == NULL)
				*head = start;
			prev = start->next;
			start = start->next->next;
		}
		else if (is_minishell_operator(start->content))
			break ;
		else
			start = move_node(prev, start, &args);
	}
	return (args);
}

t_redir_type	get_redir_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (FILE_IN);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token, ">") == 0)
		return (FILE_OUT);
	else
		return (FILE_APPEND);
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
			token = move_node(prev, token->next, &redirs);
			free(prev->content);
			free(prev);
			continue ;
		}
		else if (is_minishell_operator(token->content))
			break ;
		token = token->next;
	}
	*head = token;
	if (redirs == NULL)
		return (NO_REDIRS);
	return (redirs);
}

t_list	*new_simple_command(t_list **start, t_cmd_exec_cond cond)
{
	t_list	*cmd_node;
	t_cmd	*cmd;

	cmd_node = ft_calloc(1, sizeof(t_list));
	if (cmd_node == NULL)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (free(cmd_node), NULL);
	cmd->type = SIMPLE_CMD;
	cmd->cond = cond;
	cmd->count = get_cmd_args_count(*start);
	cmd->simple.args = get_cmd_args_list(start, cmd->count);
	if (cmd->count && cmd->simple.args == NULL)
		return (free(cmd_node), free(cmd), NULL);
	cmd->redirs = get_cmd_redirs(start);
<<<<<<< HEAD
	
	return (cmd);
=======
	if (cmd->redirs == NULL)
		return (NULL);
	cmd_node->content = cmd;
	return (cmd_node);
}

void	destroy_simple_command(t_list *command)
{
	t_cmd	*cmd;

	cmd = command->content;
	ft_lstclear(&cmd->simple.args, free);
	if (cmd->redirs != NO_REDIRS)
		ft_lstclear(&cmd->redirs, free);
	free(cmd);
	free(command);
>>>>>>> b131bc72ae501f13ee6bb9de8f9c84b099b7dc8e
}
