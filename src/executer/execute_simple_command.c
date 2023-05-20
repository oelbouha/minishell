/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:41:11 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/18 14:41:32 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	print_arr(char **arr)
{
	if (!arr)
		return ;
	for (int i = 0; arr[i]; i++)
		printf("arr[%d]: %s\n", i, arr[i]);
}

void	do_nothing(void *ptr)
{
	(void)ptr;
}

int	execute_builtin(t_builtin builtin, t_cmd *cmd, char **args)
{
	int 	fdin;
	int 	fdout;
	int 	ret;

	fdin = dup(0);
	fdout = dup(1);
	if (prep_redirs(cmd->redirs))
		return (1);
	cmd->count = arr_length(args);
	ret = builtin(cmd->count, args);
	dup2(fdin, 0);
	dup2(fdout, 1);
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
	ft_lstclear(&args, do_nothing);
	return (arr);
}

int	execute_simple_command(t_cmd *cmd, t_bool force_fork, t_bool wait_child)
{
	t_builtin	builtin;
	pid_t		pid;
	char		**args;
	char		*cmd_path;

	builtin = NULL;
	args = NULL;
	if (cmd->data.args)
	{
		args = prep_args(cmd->data.args);
		if (args == NULL || *args == NULL)
			return (free_arr(args), 0);
		cmd->count = arr_length(args);
		builtin = get_builtin(*args);
	}
	if (builtin && force_fork == FALSE)
		return (execute_builtin(builtin, cmd, args));
	pid = fork();
	if (pid)
	{
		free_arr(args);
		if (wait_child == TRUE)
			return (get_exit_status(pid));
		return ((int)pid);
	}
	if (prep_redirs(cmd->redirs))
		exit(1);
	if (builtin)
		exit(builtin(cmd->count, args));
	cmd_path = get_cmd_path(*args);
	if (cmd_path == NULL)
		command_not_found(*args);
	if (execve(cmd_path, args, get_env_arr()))
		perror("minishell");
	exit(126);
	return (0);
}
