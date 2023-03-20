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
		{
			ft_free(path);
			return (ft_strdup(cmd_path));
		}
		free(cmd_path);
	i++;
	}
	ft_free(path);
	return (NULL);
}

void	simple_command(t_shell *shell, char **env)
{
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		exit(1);
	}
	if (pid == 0)
		execute_command(shell->simple_cmd, env);
	if (pid > 0)
	{
		wait(NULL);
		ft_free(shell->simple_cmd);
	}
}

void	multiple_commands(t_shell *shell, char **env)
{
	char	**cmd;
	int		i;

	i = -1;
	while (++i <= shell->number_of_pipes)
	{	
		cmd = ft_split(shell->pipes[i], ' ');
		shell->pid = fork();
		if (shell->pid < 0)
		{
			perror("minishell: fork");
			exit(1);
		}
		if (i < shell->number_of_pipes && shell->pid == 0)
		{
			setup_pipes_for_child(i, shell->pipe1, shell->pipe2);
			execute_command(cmd, env);
		}
		if (i == shell->number_of_pipes && shell->pid == 0)
		{
			wait(NULL);
			setup_pipes_for_last_child(i, shell->pipe1, shell->pipe2);
			execute_command(cmd, env);
		}
		setup_pipes_for_next_child(i, shell->pipe1, shell->pipe2);
		// if (shell->pid > 0)
		// {
			ft_free(cmd);
		// }
	}
}

void	run_command(t_shell *shell, char **env)
{
	create_pipes(shell->pipe1, shell->pipe2);
	if (shell->number_of_pipes <= 0)
		simple_command(shell, env);
	else
		multiple_commands(shell, env);
}