/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:23:22 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/12 23:37:12 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <signal.h>

void	handle_sigint(int sig)
{
	(void)sig;
	
	signal(SIGINT, handle_sigint);
	return ;
}

int main(int c, char **v)
{
	t_heredoc *heredoc;

	(void)c;
	signal(SIGINT, handle_sigint);
	heredoc = new_heredoc_redirection(v[1]);
	return (0);
}
