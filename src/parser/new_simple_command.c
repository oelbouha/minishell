/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:41:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 10:21:18 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 *	@start: the start of the list of tokens
 *
 *	@return: the number of arguments without expansion
 *
 *	get_cmd_args_count: 
 *	counts the number of args for the command being parsed
 *	it skips redirections and stops when it encounters an operator (| in the 
 *	case of only the mandatory part + ||, && and ) in the case of bonus)
 */
int	get_cmd_args_count(t_list *start)
{
	int	count;

	count = 0;
	while (start)
	{
		if (is_redirection(start->content))
			start = start->next;
		else if (is_an_operator(start->content))
			break ;
		else
			count++;
		start = start->next;
	}
	return (count);
}

/*
 *	@head: the head of the list of tokens
 *	@count: the number of args to be extracted
 *
 *	@return: the list of arguments
 *
 *	get_cmd_args_list: 
 *	extracts the arguments in a separate list, moving each arg from 
 *	the list passed to it to a new list.
 *	it leaves redirections untouched and only removes the arguments.
 *	it stops when it encounters | for the mandatory + ||, && and )
 *	for the bonus.
 *	the @head then changed to point to the remaining of the list
 */
t_list	*get_cmd_args_list(t_list **head)
{
	t_list	*args;
	t_list	*cur;
	t_list	*prev;

	args = NULL;
	prev = NULL;
	cur = *head;
	while (cur)
	{
		if (is_redirection(cur->content))
		{
			if (prev == NULL)
				*head = cur;
			prev = cur->next;
			cur = cur->next->next;
		}
		else if (is_an_operator(cur->content))
			break ;
		else
			cur = move_node(&args, cur, prev);
	}
	if (prev == NULL)
		*head = cur;
	return (args);
}

t_list	*new_simple_command(t_list **head, t_cmd_exec_cond cond)
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
	cmd->data.args = get_cmd_args_list(head);
	cmd->count = ft_lstsize(cmd->data.args);
	cmd->redirs = get_cmd_redirs(head);
	if (cmd->redirs == NULL)
		return (free(cmd_node), destroy_simple_command(cmd), NULL);
	cmd_node->content = cmd;
	return (cmd_node);
}

void	destroy_simple_command(t_cmd *cmd)
{
	ft_lstclear(&cmd->data.args, free);
	if (cmd->redirs != NO_REDIRS)
		ft_lstclear(&cmd->redirs, (t_lstdel)destroy_redir);
	free(cmd);
}
