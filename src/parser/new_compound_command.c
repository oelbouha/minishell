/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_compound_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:57:36 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/15 23:16:40 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// compound command end when:
// 		")" : if we have an opened parenthese
// 		"&&/||": if we do not have an opened parenthes
int	get_compound_count(t_list *start, t_bool parentheses)
{
	int	count;
	int	_parentheses;

	_parentheses = (parentheses == TRUE);
	if (_parentheses)
		start = start->next;
	count = 1;
	while (start)
	{
		if (ft_strcmp(start->content, "|") == 0)
			count++;
		else if (ft_strcmp(start->content, ")") == 0)
		{
			_parentheses--;
			if (_parentheses == 0)
				break ;
		}
		else if (ft_strcmp(start->content, "(") == 0)
			_parentheses++;
		else if (!_parentheses && BONUS && ft_templatecmp(start->content, "&&:||", ':'))
			break ;
		start = start->next;
	}
	return (count);
}

t_cmd	*new_compound_command(t_list *start, t_cmd_exec_cond cond)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = COMPOUND_CMD;
	cmd->cond = cond;
	cmd->data.compound.parentheses = FALSE;
	if (ft_strcmp(start->content, "(") == 0)
		cmd->data.compound.parentheses = TRUE;
	cmd->count = get_compound_count(start, cmd->data.compound.parentheses);
	ft_printf("count: %d\n", cmd->count);
	return (cmd);
}
