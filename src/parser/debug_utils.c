#include "parser.h"

void	print_simple_cmd(t_cmd *cmd)
{
	char cond[3][5] = {"NONE", "AND", "OR"};
	ft_printf("Simple command:\n");
	ft_printf("\tcond: %s\n", cond[cmd->cond]);
	ft_printf("\targc: %d\n", cmd->count);
	if (cmd->count)
	{
		ft_printf("\targv: [ %s", cmd->data.simple.args[0]);
		for (int i = 1; cmd->data.simple.args[i]; i++)
			ft_printf(", %s", cmd->data.simple.args[i]);
		ft_printf(" ]\n");
	}
	t_list *cur = cmd->redirs;
	ft_printf("\tredirections:\n");
	while (cur)
	{
		t_redir *r = cur->content;
		if (r->type == HEREDOC)
			ft_printf("\t\theredoc\n");
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
	return ;
}
