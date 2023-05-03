/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:17 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/29 10:12:54 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "debug.h"

int main()
{
	while (1)
	{
		char *line = read_line(0);
		t_list	*list = split_line(line);
		t_list	*cmd = new_simple_command(&list, NONE);
		for (t_list *cur = cmd; cur;)
		{
			print_simple_cmd(cur->content);
			cur = cur->next;
		}
		free(line);
		t_list *cur = list;
		while (cur)
		{
			if (cur == list)
				ft_printf("\n:: ");
			ft_printf("%s ::", cur->content);
			if (cur->next)
				ft_printf(" ");
			else
				ft_printf("\n");
			cur = cur->next;
		}
	//	ft_lstclear(&list, free);
		ft_lstclear(&cmd, (t_lstdel)destroy_command);
	}
}
