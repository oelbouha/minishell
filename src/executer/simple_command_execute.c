/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:38:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 10:42:00 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

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
	char		*path;
	int			ret;

	(void)force_fork;
	builtin = get_builtin(cmd->data.args->content);
	if (builtin && force_fork == FALSE)
	{
		args = prep_args(cmd->data.args); // if alloc fails exit
		ret = builtin(cmd->count, args);
		return (free(args), ret);
	}
	pid = fork();
	if (pid)
	{
		if (wait_child == TRUE)
			return (get_exit_status(pid));
		return ((int)pid);
	}
	if (ft_strcmp(cmd->data.args->content, "yes") == 0)
		close(3);
	prep_redirs(cmd->redirs); // handles its errors and exit if any
	path = get_cmd_path(cmd->data.args->content);
	if (path == NULL)
		return (command_not_found(cmd->data.args->content));
	args = prep_args(cmd->data.args); // if alloc fails exit
	if (builtin)
		exit(builtin(cmd->count, args));
	else if (execve(path, args, get_env_arr()))
		perror("minishell");
	exit(-1);
	return (0);
}
