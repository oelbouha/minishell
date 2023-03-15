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
	if (ft_search(arr[0] , '<') || ft_search(arr[0] , '>'))
		return (1);
	if (ft_search(arr[i] , '<') || ft_search(arr[i] , '>'))
		return (1);
	return (0);
}

int	count_pipes(char **arr)
{
	int i;

	if (!arr[0] || !arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	parse_error()
{
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		exit (1);
	}
	if (pid == 0)
	{
		ft_putstr_fd("minishell: parse error\n", 2);
		exit (130);
	}
}

int	check_pipes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' && str[i + 1] == '|' && str[i + 2] == '|')
			return (1);
	}
	return (0);
}

void	store_line(char *line, char **env)
{
	t_shell	shell;

	shell.pipes = split(line, '|');
	shell.number_of_pipes = count_pipes(shell.pipes) - 1;
	printf("count ==> %d\n", shell.number_of_pipes);
	if (ft_search(line, '|'))
	{
		if ((!shell.pipes[0] && check_pipes(line) == 1) || count_pipes(shell.pipes) == 1 || check_pipes(line) == 1)
			parse_error();
	}
	if (!ft_search(line, '|'))
	{
		if (shell.pipes)
			ft_free(shell.pipes);
		shell.simple_cmd = ft_split(line, ' ');
		run_command(&shell, env);
	}
	if (shell.number_of_pipes > 0 && !check_pipes(line))
	{
		if (contains_redirections(shell.pipes, shell.number_of_pipes))
		{
			// handle redirections with pipes
		}
		else
		{
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

