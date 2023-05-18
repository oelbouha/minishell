/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:30:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 13:32:44 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

void	print_cmd(t_list *lst, int parser_output)
{
	for (t_list *cur = command; parser_output && cur; indent++)
		{
			print_cmd(cur->content, indent);
			cur = cur->next;
		}

}

int	main(int c, char **v, char **e)
{
	char	*line;
	t_list	*tokens;
	t_list	*command;
	int		err;
	int		parser_output = 1;
	int		lexer_output = 0;

	(void)c;
	(void)v;
	setup(e);
	while (1)
	{
		int		indent = 0;
		line = read_line(1);
		if (line == NULL)
			return (get_last_status());
		tokens = tokenize(line);
		err = analyze(&tokens);
		command = new_command(&tokens, NONE);
		print_cmd(command, parser_output);
		execute(command);
		free(line);
		ft_lstclear(&command, (t_lstdel)destroy_command);
		if (get_last_status() < 0)
			return (1);
	}
}
