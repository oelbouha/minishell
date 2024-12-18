/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_compound_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:57:36 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 10:20:44 by ysalmi           ###   ########.fr       */
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

	if (start == NULL)
		return (0);
	count = 1;
	while (start)
	{
		if (ft_strcmp(start->content, "|") == 0)
			count++;
		start = start->next;
	}
	return (count);
}

t_list	**get_commands_arr(t_list **head, int count)
{
	t_list	**arr;
	t_list	*start;
	int		i;

	arr = ft_calloc(count, sizeof(t_list *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	start = *head;
	while (start)
	{
		if (ft_strcmp(start->content, "|") == 0)
			ft_lstdel_first(&start, free);
		else
			arr[i++] = new_simple_command(&start, NONE);
	}
	*head = start;
	return (arr);
}

t_list	*new_compound_command(t_list **start, t_cmd_exec_cond cond)
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
	cmd->count = get_commands_count(*start);
	cmd->data.arr = get_commands_arr(start, cmd->count);
	if (cmd->data.arr == NULL)
		return (free(cmd_node), free(cmd), NULL);
	cmd_node->content = cmd;
	return (cmd_node);
}

void	destroy_compound_command(t_cmd *cmd)
{
	int		i;

	i = -1;
	while (++i < cmd->count)
		ft_lstclear(&(cmd->data.arr[i]), (t_lstdel)destroy_command);
	if (cmd->redirs && cmd->redirs != (t_list *)-1)
		ft_lstclear(&cmd->redirs, (t_lstdel)destroy_redir);
	free(cmd->data.arr);
	free(cmd);
}
