#include "parser.h"
void	print_cmd(t_cmd *cmd, int n);

void	print_tabs(int n)
{
	while (n-- > 0)
		ft_printf("\t");
}

void	print_heredoc(t_redir *r, int n)
{
	int	newline = 0;
	print_tabs(n);
	ft_printf("|\theredoc: %d - ", r->to.heredoc.fd);
	if (r->to.heredoc.expand == TRUE)
		ft_printf("expand\n");
	else
		ft_printf("no-expand\n");
	char s;
	print_tabs(n);
	ft_printf("|\t\t|");
	while (read(r->to.heredoc.fd, &s, 1))
	{
		if (newline)
		{
			newline = 0;
			print_tabs(n);
			ft_printf("|\t\t|");
		}
		write(1, &s, 1);
		if (s == '\n')
			newline = 1;
	}
}

void	print_redirections(t_list *redirs, int n, char wall)
{
	t_list *cur = redirs;
	if (cur == NO_REDIRS || cur == NULL)
		return ;
	print_tabs(n);
	ft_printf("%c redirections:\n", wall);
	while (cur)
	{
		t_redir *r = cur->content;
		if (r->type == HEREDOC)
			print_heredoc(r, n);
		else
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
	char cond[3][5] = {"NONE", "AND", "OR"};

	print_tabs(n);
	ft_printf("+------------\n");
	print_tabs(n);
	ft_printf("| cond: %s\n", cond[cmd->cond]);
	print_tabs(n);
	ft_printf("| argc: %d\n", cmd->count);
	if (cmd->count && cmd->simple.args)
	{
		print_tabs(n);
		ft_printf("| argv: [ ");
		t_list *cur = cmd->simple.args;
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
	print_tabs(n);
	ft_printf("* subshell: ");
	if (cmd->compound.subshell == TRUE)
		ft_printf("Yes\n");
	else
		ft_printf("No\n");
	for (int i = 0; i < cmd->count; i++)
	{
		int j = 1;
		for (t_list *cur = cmd->compound.arr[i]; cur;)
		{
			print_cmd(cur->content, n + j++);
			cur = cur->next;
		}
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
}
