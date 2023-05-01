/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:17 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/30 16:08:11 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "debug.h"

int main()
{
	int	indent = 0;

	while (1)
	{
		char *line = read_line(0);
		t_list	*list = split_line(line);
		t_list	*cmd = new_command(&list, NONE);
		for (t_list *cur = cmd; cur;)
		{
			print_cmd(cur->content, indent++);
			cur = cur->next;
		}
		free(line);
		ft_lstclear(&cmd, (t_lstdel)destroy_command);
		indent = 0;
	}
}
