#include "parser.h"

void	print_heredoc(t_redir *r)
{
	ft_printf("\t\theredoc: %d - ", r->to.heredoc.fd);
	if (r->to.heredoc.expand == TRUE)
		ft_printf("expand\n");
	else
		ft_printf("no-expand\n");
	char s;
	write(1, "\t\t\t", 3);
	while (read(r->to.heredoc.fd, &s, 1))
	{
		write(1, &s, 1);
		if (s == '\n')
			write(1, "\t\t\t", 3);
	}
	write(1, "\n", 1);
}

void	print_redirections(t_list *redirs)
{
	t_list *cur = redirs;
	ft_printf("\tredirections:\n");
	while (cur)
	{
		t_redir *r = cur->content;
		if (r->type == HEREDOC)
			print_heredoc(r);
		else
		{
			ft_printf("\t\t%s: ", r->to.filename);
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

void	print_simple_cmd(t_cmd *cmd)
{
	char cond[3][5] = {"NONE", "AND", "OR"};
	ft_printf("Simple command:\n");
	ft_printf("\tcond: %s\n", cond[cmd->cond]);
	ft_printf("\targc: %d\n", cmd->count);
	if (cmd->count && cmd->data.simple.args)
	{
		ft_printf("\targv: [ %s", cmd->data.simple.args[0]);
		for (int i = 1; cmd->data.simple.args[i]; i++)
			ft_printf(", %s", cmd->data.simple.args[i]);
		ft_printf(" ]\n");
	}
	print_redirections(cmd->redirs);
	return ;
}
