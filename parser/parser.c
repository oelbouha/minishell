/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:18:59 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/10 19:23:13 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print(char **arr)
{
	if (!arr)
		return ;
	int i = -1;
	while (arr[++i])
		printf("arr [%d] ==> %s\n",i , arr[i]);
}

int	contains_redirections(char **arr, int i)
{
	if (!arr[0] || !arr)
		return (1);
	if (ft_search(arr[0] , '<') || ft_search(arr[0] , '>'))
		return (1);
	if (ft_search(arr[i] , '<') || ft_search(arr[i] , '>'))
		return (1);
	return (0);
}

void	setup_infile(char *infile)
{
	int		fd;

	fd = open(infile, O_RDONLY);
	if (access(infile, F_OK) < 0)
		print_error_msg(infile, ": No such file or directory", 0, 0);
	if (access(infile, R_OK) < 0)
		print_error_msg(infile, ": permission denied", 1, 0);
	dup2(fd, 0);
}

void	setup_outfile(char *outfile)
{
	int		fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == - 1)
	{
		perror("minishell");
		exit(1);
	}
	dup2(fd, 1);
}


void	store_line(char *line, char **env)
{
	t_redirections	redirections;
	t_shell			shell;

	shell.pipes = split(line, '|');
	shell.number_of_pipes = count_pipes(shell.pipes) - 1;
	if (ft_search(line, '|') && check_pipe_error(shell.pipes, line))
		parse_error();
	if (!ft_search(line, '|') && !contains_redirections(shell.pipes, shell.number_of_pipes))
	{
		// run simple command
		shell.simple_cmd = ft_split(shell.pipes[0], ' ');
		ft_free(shell.pipes);
		run_command(&shell, env);
	}
	if (!ft_search(line, '|') && (ft_search(line, '>') || ft_search(line, '<')))
	{
		(void)redirections;
		// run simple command with redirections
		shell.cmds = ft_split(shell.pipes[0], ' ');
		ft_free(shell.pipes);
		print(shell.cmds);
		if (!valid_redirection(shell.cmds))
		{
			// printf("valid \n");
			setup_redirections(shell.cmds, &redirections);
		}
	}
	if (shell.number_of_pipes > 0)
	{
		printf("here\n");
		if (contains_redirections(shell.pipes, shell.number_of_pipes))
		{
		}
		else if (!check_pipe_error(shell.pipes, line))
		{
			// run commands with pipes
			run_command(&shell, env);
		}
	}
}

void	read_input(char **env)
{
	char	*line;

	while (1)
	{
		line = readline("");
		store_line(line, env);
	}
}

