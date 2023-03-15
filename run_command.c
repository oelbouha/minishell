/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:27:15 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/12 13:27:28 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_path(char *cmd)
{
	if (*cmd == '/' || *cmd == '.' || ft_search(cmd, '/'))
	{
		if (*cmd == '/' && access(cmd, F_OK) < 0)
			print_error_msg(cmd, ": No such file or directory", 0, 0);
		else if (*cmd == '.' && access(cmd,  F_OK) < 0)
			print_error_msg(cmd, ": No such file or directory", 127, 0);
		else if (*cmd == '.' && access(cmd,  X_OK) < 0)
			print_error_msg(cmd, ": permission denied", 126, 0);
		else if (access(cmd, F_OK) < 0)
			print_error_msg(cmd, ": No such file or directory", 0, 0);
		else if (access(cmd, X_OK) < 0)
			print_error_msg(cmd, ": permission denied", 0, 0);
		return (0);
	}
	return (1);
}

// char	*path_from_env(char **env)
// {
// 	char	*path;
// 	int		i;

// 	path = NULL;
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "PATH=/", 6) == 0)
// 		{
// 			path = ft_strchr(env[i], '=') + 1;
// 			return (path);
// 		}
// 		i++;
// 	}
// 	path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
// 	return (path);
// }

char	*make_path(char *cmd)
{
	char	**path;
	char	*cmd_path;
	char	*s;
	int		i;

	cmd_path = NULL;
	path = ft_split(PATH, ':');
	i = 0;
	while (path[i])
	{
		s = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(s, cmd);
		free(s);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		free(path[i]);
	i++;
	}
	free(path);
	return (NULL);
}

void	setup_pipes_for_child(int i, int *pipe1, int *pipe2, int number_of_pipes)
{
	(void)number_of_pipes;
	if (i % 2 != 0 && i > 0)
	{
		dup2(pipe1[0], 0);
		dup2(pipe2[1], 1);
		close (pipe1[1]);
		close (pipe2[0]);
	}
	else if (i == 0)
	{
		dup2(pipe1[1], 1);
		close(pipe1[0]);
		close(pipe2[0]);
		close(pipe2[1]);
	}
	else if (i % 2 == 0 && i > 0)
	{
		dup2(pipe2[0], 0);
		dup2(pipe1[1], 1);
		close(pipe1[0]);
		close(pipe2[1]);
	}
}

void	setup_pipes_for_last_child(int i, int *pipe1, int *pipe2, int number_of_pipes)
{
	(void)number_of_pipes;
	if (i % 2)
	{
		dup2(pipe1[0], 0);
		close (pipe1[1]);
		close (pipe2[1]);
		close (pipe2[0]);
	}
	else
	{
		dup2(pipe2[0], 0);
		close (pipe1[1]);
		close (pipe2[1]);
		close (pipe1[0]);
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

void	simple_command(t_shell *shell, char **env)
{
	char	*path;
	int		pid;

	path = make_path(shell->simple_cmd[0]);
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		exit(1);
	}
	if (pid == 0)
		execute_command(shell->simple_cmd, path, env);
	else
	{
		wait(NULL);
		free(path);
		ft_free(shell->simple_cmd);
	}
}

void	multiple_commands(t_shell *shell, char **env)
{
	char 	*path;
	char	**cmd;
	int		pid;
	int		i;

	if (pipe(shell->pipe1) < 0 || pipe(shell->pipe2) < 0)
	{
		perror("minishell: pipe");
		exit(1);
	}
	i = -1;
	while (++i <= shell->number_of_pipes)
	{	
		cmd = ft_split(shell->pipes[i], ' ');
		// print(cmd);
		path = make_path(cmd[0]);
		pid = fork();
		if (pid < 0)
		{
			perror("minishell: fork");
			exit(1);
		}
		if (i < shell->number_of_pipes && pid == 0)
		{
			setup_pipes_for_child(i, shell->pipe1, shell->pipe2, shell->number_of_pipes);
			execute_command(cmd, path, env);
		}
		if (i == shell->number_of_pipes && pid == 0)
		{
			wait(NULL);
			setup_pipes_for_last_child(i, shell->pipe1, shell->pipe2, shell->number_of_pipes);
			execute_command(cmd, path, env);
		}
		setup_pipes_for_next_child(i, shell->pipe1, shell->pipe2);
		if (pid > 0)
		{
			ft_free(cmd);
			free(path);
		}
	}
}

void	run_command(t_shell *shell, char **env)
{

	if (shell->number_of_pipes == 0)
		simple_command(shell, env);
	else
	{
		multiple_commands(shell, env);
	}
}