/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:05:06 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/15 12:05:32 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(int *pipe1, int *pipe2)
{
	int pid;

	if (pipe(pipe1) < 0 || pipe(pipe2) < 0)
	{
		pid = fork();
		if (pid == 0)
		{
			perror("minishell: pipe");
			exit(1);
		}
	}
}

void	setup_pipes_for_child(int i, int *pipe1, int *pipe2)
{
	if (i % 2 != 0 && i > 0)
	{
		dup2(pipe1[0], 0);
		dup2(pipe2[1], 1);
		close(pipe2[1]);
		close (pipe2[0]);
		close(pipe1[1]);
		close (pipe1[0]);
	}
	else if (i == 0)
	{
		dup2(pipe1[1], 1);
		close(pipe1[0]);
		close(pipe2[1]);
		close (pipe2[0]);
		close(pipe1[1]);
		close (pipe1[0]);
	}
	else if (i % 2 == 0 && i > 0)
	{
		dup2(pipe2[0], 0);
		dup2(pipe1[1], 1);
		close(pipe2[1]);
		close (pipe2[0]);
		close(pipe1[1]);
		close (pipe1[0]);
	}
}

void	setup_pipes_for_last_child(int i, int *pipe1, int *pipe2)
{
	if (i % 2)
	{
		dup2(pipe1[0], 0);
		close (pipe1[1]);
		close (pipe1[0]);
		close (pipe2[1]);
		close (pipe2[0]);
	}
	else
	{
		dup2(pipe2[0], 0);
		close (pipe1[1]);
		close (pipe1[0]);
		close (pipe2[1]);
		close (pipe2[0]);
	}
}

void	setup_pipes_for_next_child(int i, int *pipe1, int *pipe2)
{
	if (i % 2)
	{
		close (pipe1[1]);
		close (pipe1[0]);
		if (pipe(pipe1) < 0)
		{
			perror("pipex: pipe");
			exit(1);
		}
	}
	else
	{
		close(pipe2[0]);
		close(pipe2[1]);
		if (pipe(pipe2) < 0)
		{
			perror("pipex: pipe");
			exit(1);
		}
	}
}