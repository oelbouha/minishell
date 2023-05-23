/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:41:11 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/23 16:34:42 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	do_nothing(void *ptr)
{
	(void)ptr;
}

int	execute_builtin(t_builtin builtin, t_cmd *cmd, char **args)
{
	int		fdin;
	int		fdout;
	int		ret;

	ret = 0;
	fdin = dup(0);
	fdout = dup(1);
	if (prep_redirs(cmd->redirs))
		ret = 1;
	if (ret == 0)
	{
		cmd->count = arr_length(args);
		ret = builtin(cmd->count, args);
	}
	dup2(fdin, 0);
	dup2(fdout, 1);
	close(fdin);
	close(fdout);
	free_arr(args);
	return (ret);
}

char	**prep_args(t_list *args_lst)
{
	char	**arr;
	t_list	*args;

	args = expand(args_lst);
	if (args == NULL)
		return (NULL);
	arr = ft_lst_to_arr(args);
	if (arr == NULL)
		return (ft_lstclear(&args, free), NULL);
	ft_lstclear(&args, do_nothing);
	return (arr);
}

int	execute_cmd(t_cmd *cmd, t_builtin builtin, char **args)
{
	char	*cmd_path;

	if (prep_redirs(cmd->redirs))
		exit(1);
	if (builtin)
		exit(builtin(cmd->count, args));
	if (args)
	{
		cmd_path = get_cmd_path(*args);
		if (cmd_path == NULL)
			command_not_found(*args);
		if (execve(cmd_path, args, get_env_arr()))
		{
			free(cmd_path);
			free_arr(args);
			perror("minishell");
		}
		exit(126);
	}
	exit(0);
	return (0);
}

int	execute_simple_command(t_cmd *cmd, t_bool force_fork, t_bool wait_child)
{
	t_builtin	builtin;
	pid_t		pid;
	char		**args;

	args = NULL;
	builtin = NULL;
	if (cmd->data.args)
	{
		args = prep_args(cmd->data.args);
		if (args == NULL || *args == NULL)
			return (free_arr(args), 0);
		cmd->count = arr_length(args);
		builtin = get_builtin(*args);
		if (builtin && force_fork == FALSE)
			return (execute_builtin(builtin, cmd, args));
	}
	pid = fork();
	if (pid)
	{
		free_arr(args);
		if (wait_child == TRUE)
			return (get_exit_status(pid));
		return ((int)pid);
	}
	signal(SIGINT, SIG_DFL);
	return (execute_cmd(cmd, builtin, args));
}
