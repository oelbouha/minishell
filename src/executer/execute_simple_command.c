/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:38:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/14 16:11:31 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"


void	prep_redirs(t_list *redirs)
{
	(void)redirs;
	return;
}

char	*get_cmd_path(const char *cmd_name)
{
	return ((char *)cmd_name);
}

char	**prep_args(t_list *args_lst)
{
	return (ft_lst_to_arr(args_lst));
}

int	is_builtind(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}

int	command_not_found(const char *cmd_name)
{
	(void)cmd_name;
	ft_putstr_fd("command not found\n", 2);
	return (127);
}

int	execute_simple_command(t_cmd *cmd, t_bool force_fork, t_bool wait_child)
{
	pid_t		pid;
	t_builtin	builtin;
	char		**args;
	int			ret;

	builtin = get_builtin(cmd->data._simple.args->content);
	if (builtin && force_fork == FALSE)
	{
		args = prep_args(cmd->data._simple.args); // if alloc fails exit
		ret = builtin(cmd->count, args);
		return (free(args), ret);
	}
	pid = fork();
	if (pid)
	{
		// CLOSE PIPE_IN;
		if (wait_child == TRUE)
			return (get_exit_status(pid));
		return (0);
	}
	prep_redirs(cmd->redirs); // handles its errors and exit if any
	cmd->data._simple.path = get_cmd_path(cmd->data._simple.args->content);
	if (cmd->data._simple.path == NULL)
		return (command_not_found(cmd->data._simple.args->content));
	args = prep_args(cmd->data._simple.args); // if alloc fails exit
	if (builtin)
		exit(builtin(cmd->count, args));
	if (execve(cmd->data._simple.path, args, get_env_arr()))
		return (perror("minishell"), exit(-1), 0);
	return (0);
}
