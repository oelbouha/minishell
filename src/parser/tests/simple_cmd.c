/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:17 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/13 23:03:51 by ysalmi           ###   ########.fr       */
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
		t_cmd	*cmd = new_simple_command(list, NONE);
		print_simple_cmd(cmd);
	}
}
