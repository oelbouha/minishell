/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:30:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/26 15:41:20 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

void	print_cmmd(t_list *lst, int parser_output)
{
	int	indent;

	indent = 0;
	for (t_list *cur = lst; parser_output && cur; indent++)
	{
		print_cmd(cur->content, indent);
		cur = cur->next;
	}
}
	
char	*get_line(void)
{
	char	*trimmed;
	char	*line;

	line = NULL;
	while (ft_issubset(" \t", line))
	{
		free(line);
		set_state(0);
		line = readline("→ ");
		if (line == NULL)
			return (line);
	}
	add_history(line);
	trimmed = ft_strtrim(line, " \t");
	return (free(line), trimmed);
}

int	main(int c, char **v, char **e)
{
	char	*line;
	t_list	*tokens;
	t_list	*command;
	int		err;
	int		parser_output = 1;

	(void)c;
	(void)v;
	if (setup(e))
		return (destroy(), 1);
	while (1)
	{
		line = get_line();
		if (line == NULL)
			return (destroy(), get_last_status());
		tokens = tokenize(line);
		err = analyze(&tokens);
		command = new_command(&tokens, NONE);
		print_cmmd(command, parser_output);
		if (err && get_state() == 0)
			set_last_status(258);
		else if (get_state() == 0)
		{
			set_state(1);
			execute(command);
		}
		free(line);
		ft_lstclear(&command, (t_lstdel)destroy_command);
		if (get_last_status() < 0)
			return (1);
	}
}
