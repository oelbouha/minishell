/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_compound_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:57:36 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/03 17:41:05 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//		get the number of commands in a compound command
//	compound command is a pipeline "|" of simple or compound commands either
//	wraped in parentheses or not
//		-the commands count is the number of pipes plus 1
//		-only incerement if we are outside a compound command
//		-stop counting if encountered the closing parenthese
//		 or when there is no opening parenthese and find && or ||

int	get_commands_count(t_list *start)
{
	int	count;
	int	parentheses;

	if (start == NULL)
		return (0);
	parentheses = 0;
	count = 1;
	while (start)
	{
		if (ft_strcmp(start->content, "|") == 0 && parentheses == 0)
			count++;
		else if (ft_strcmp(start->content, "(") == 0)
			parentheses++;
		else if (ft_strcmp(start->content, ")") == 0 && --parentheses < 0)
				break ;
		else if (parentheses == 0  && BONUS
			&& ft_templatecmp(start->content, "&&:||", ':'))
			break ;
		start = start->next;
	}
	return (count);
}
t_list	*new_subshell_command(t_list **start, t_cmd_exec_cond cond);

t_list	**get_commands_arr(t_list **head, int count)
{
	t_list	**cmds;
	t_list	*start;
	//t_list	*prev;
	//t_cmd	*cmd;
	int		i;

	cmds = ft_calloc(count, sizeof(t_list *));
	if (cmds == NULL)
		return (NULL);
	if (count == 1)
	{
		cmds[0] = new_command(head, NONE);
		return (cmds);
	}
	i = 0;
	start = *head;
	while (start)
	{
		if (BONUS && ft_templatecmp(start->content, "&&:||:)", ':'))
			break ;
		else if (ft_strcmp(start->content, "|") == 0)
			ft_lstdel_first(&start, free);
		else if (BONUS && ft_strcmp(start->content, "(") == 0)
		{
			cmds[i++] = new_subshell_command(&start, NONE);
			/*
			prev = start;
			start = start->next;
			ft_lstdelone(prev, free);
			cmds[i] = new_compound_command(&start, NONE);
			cmd = cmds[i]->content;
			cmd->compound.subshell = TRUE;
			cmds[i]->next = get_next_cmd(&start);
			prev = start;
			start = start->next;
			ft_lstdelone(prev, free);
			cmd->redirs = get_cmd_redirs(&start);
			i++;*/
		}
		else
			cmds[i++] = new_simple_command(&start, NONE);
	}
	*head = start;
	return (cmds);
}

t_list	*new_subshell_command(t_list **start, t_cmd_exec_cond cond)
{
	t_list	*cmd_node;
	t_cmd	*cmd;

	cmd_node = ft_calloc(1, sizeof(t_list));
	if (cmd_node == NULL)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (free(cmd_node), NULL);
	cmd->type = COMPOUND_CMD;
	cmd->cond = cond;
	cmd->compound.subshell = TRUE;
	ft_lstdel_first(start, free);
	cmd->count = get_commands_count(*start);
	cmd->compound.cmds = get_commands_arr(start, cmd->count);
	if (cmd->compound.cmds == NULL)
		return (free(cmd_node), free(cmd), NULL);
	cmd_node->content = cmd;
	cmd_node->next = get_next_cmd(start);
	ft_lstdel_first(start, free);
	cmd->redirs = get_cmd_redirs(start);
	return (cmd_node);

}

t_list	*new_compound_command(t_list **start, t_cmd_exec_cond cond)
{
	t_list	*cmd_node;
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = COMPOUND_CMD;
	cmd->cond = cond;
	cmd->compound.subshell = FALSE;
	cmd->count = get_commands_count(*start);
	cmd->compound.cmds = get_commands_arr(start, cmd->count);
	cmd_node = ft_calloc(1, sizeof(t_list));
	if (cmd_node == NULL)
		return (destroy_compound_command(cmd), NULL);
	cmd_node->content = cmd;
	return (cmd_node);
}

void	destroy_compound_command(t_cmd *cmd)
{
	int		i;

	i = -1;
	while (++i < cmd->count)
		ft_lstclear(&(cmd->compound.cmds[i]), (t_lstdel)destroy_command);
	if (cmd->redirs && cmd->redirs != NO_REDIRS)
		ft_lstclear(&cmd->redirs, (t_lstdel)destroy_redir);
	free(cmd->compound.cmds);
	free(cmd);
}
