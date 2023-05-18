/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:30:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 20:36:13 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

void	print_cmmd(t_list *lst, int parser_output)
{
	int		indent = 0;
	for (t_list *cur = lst; parser_output && cur; indent++)
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
	int		parser_output = 0;
	int		lexer_output = 0;

	(void)c;
	(void)v;
	setup(e);
	while (1)
	{
		line = read_line(1);
		if (line == NULL)
			return (get_last_status());
		tokens = tokenize(line);
		err = analyze(&tokens);
		if (lexer_output)
			print(tokens);
		command = new_command(&tokens, NONE);
		print_cmmd(command, parser_output);
		if (err)
			set_last_status(258);
		else
			execute(command);
		free(line);
		ft_lstclear(&command, (t_lstdel)destroy_command);
		if (get_last_status() < 0)
			return (1);
	}
}
