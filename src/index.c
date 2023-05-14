/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:30:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/14 14:05:52 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

int	main(int c, char **v, char **e)
{
	char	*line;
	t_list	*tokens;
	t_list	*command;
	int		err;

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
		print(tokens);
		command = new_command(&tokens, NONE);
		for (t_list *cur = command; cur; indent++)
		{
			print_cmd(cur->content, indent);
			cur = cur->next;
		}
		execute(command);
		ft_printf("executed [ %d ]\n", get_last_status());
		free(line);
		ft_lstclear(&command, (t_lstdel)destroy_command);
	}
}