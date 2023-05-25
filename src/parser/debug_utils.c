/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:00:10 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/25 12:03:04 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_cmd(t_cmd *cmd, int n);

void	print_tabs(int n)
{
	while (n-- > 0)
		ft_printf("\t");
}

void	print_heredoc(t_redir *r, int n)
{
	print_tabs(n);
	ft_printf("|\theredoc: %d - ", r->to.fd.val);
	if (r->to.fd.expand == TRUE)
		ft_printf("expand\n");
	else
		ft_printf("no-expand\n");
}

void	print_redirections(t_list *redirs, int n, char wall)
{
	t_list	*cur;
	t_redir	*r;
	
	cur = redirs;
	if (cur == NO_REDIRS || cur == NULL)
		return ;
	print_tabs(n);
	ft_printf("%c redirections:\n", wall);
	while (cur)
	{
		r = cur->content;
		if (r->type == HEREDOC)
			print_heredoc(r, n);
		else if (r->type != PIPE_IN && r->type != PIPE_OUT)

		{
			print_tabs(n);
			ft_printf("%c\t%s: ", wall, r->to.filename);
			if (r->type == FILE_IN)
				ft_printf("input\n");
			else if (r->type == FILE_OUT)
				ft_printf("output [trunc]\n");
			else
				ft_printf("output [append]\n");
		}
		cur = cur->next;
	}
}

void	print_simple_cmd(t_cmd *cmd, int n)
{
	t_list	*cur;
	char	cond[3][5] = {"NONE", "AND", "OR"};

	print_tabs(n);
	ft_printf("+------------\n");
	print_tabs(n);
	ft_printf("| cond: %s\n", cond[cmd->cond]);
	print_tabs(n);
	ft_printf("| argc: %d\n", cmd->count);
	if (cmd->count && cmd->data.args)
	{
		print_tabs(n);
		ft_printf("| argv: [ ");
		cur = cmd->data.args;
		while (cur)
		{
			ft_printf("%s", cur->content);
			cur = cur->next;
			if (cur)
				ft_printf(", ");
		}
		ft_printf(" ]\n");
	}
	print_redirections(cmd->redirs, n, '|');
	print_tabs(n);
	ft_printf("+------------\n");
	return ;
}

void	print_compound_cmd(t_cmd *cmd, int n)
{
	char cond[3][5] = {"NONE", "AND", "OR"};
	print_tabs(n);
	ft_printf("+**********************************+\n");
	print_tabs(n);
	ft_printf("* cond: %s\n", cond[cmd->cond]);
	for (int i = 0; i < cmd->count; i++)
	{
		int j = 1;
		for (t_list *cur = cmd->data.arr[i]; cur;)
		{
			print_cmd(cur->content, n + j++);
			cur = cur->next;
		}
	}
	print_redirections(cmd->redirs, n, '*');
	print_tabs(n);
	ft_printf("+**********************************+\n");
}

void	print_subshell_cmd(t_cmd *cmd, int n)
{
	char cond[3][5] = {"NONE", "AND", "OR"};
	print_tabs(n);
	ft_printf("+############# subshell ############+\n");
	print_tabs(n);
	ft_printf("* cond: %s\n", cond[cmd->cond]);
	int	indent = n;
	for (t_list *cur = cmd->data.lst; cur;)
	{
		print_cmd(cur->content, ++indent);
		cur = cur->next;
	}
	print_redirections(cmd->redirs, n, '*');
	print_tabs(n);
	ft_printf("+**********************************+\n");
}

void	print_cmd(t_cmd *cmd, int n)
{
	if (cmd->type == SIMPLE_CMD)
		print_simple_cmd(cmd, n);
	else if (cmd->type == COMPOUND_CMD)
		print_compound_cmd(cmd, n);
	else if (cmd->type == SUBSHELL_CMD)
		print_subshell_cmd(cmd, n);
}
