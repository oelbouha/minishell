/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:41:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/16 23:36:31 by ysalmi           ###   ########.fr       */
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

char	**get_cmd_args_arr(t_list *start, int count)
{
	char	**arr;
	int		i;

	if (count < 1)
		return (NULL);
	arr = ft_calloc(count + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (start)
	{
		if (is_redirection(start->content))
			start = start->next;
		else if (is_minishell_operator(start->content))
			break ;
		else
			arr[i++] = start->content;
		start = start->next;
	}
	return (arr);
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

t_list	*get_cmd_redirs(t_list *token)
{
	t_list			*redirs;
	t_list			*redir;
	t_redir_type	type;

	redirs = NULL;
	while (token)
	{
		if (is_redirection(token->content))
		{
			type = get_redir_type(token->content);
			token = token->next;
			if (type == HEREDOC)
			{
				ft_lstremove_if(&redirs, (t_lstcmp)is_heredoc, (t_lstdel)del_heredoc);
				redir = new_heredoc_redirection(token->content);
			}
			else
				redir = new_file_redirection(token->content, type);
			if (redir == NULL)
				return (ft_lstclear(&redirs, free), NULL);
			ft_lstadd_back(&redirs, redir);
		}
		else if (is_minishell_operator(token->content))
			break ;
		token = token->next;
	}
	if (redirs == NULL)
		return ((t_list *)-1);
	return (redirs);
}

t_list	*new_simple_command(t_list *start, t_cmd_exec_cond cond)
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
	cmd->count = get_cmd_args_count(start);
	cmd->simple.args = get_cmd_args_arr(start, cmd->count);
	if (cmd->count && cmd->simple.args == NULL)
		return (free(cmd_node), free(cmd), NULL);
	cmd->redirs = get_cmd_redirs(start);
	if (cmd->redirs == NULL)
		return (NULL);
	cmd_node->content = cmd;
	return (cmd_node);
}
