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

void	do_nth(void *ptr)
{
	(void)ptr;
}

int	execute_builtin(t_builtin builtin, t_cmd *cmd, char **args)
{
	int fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	prep_redirs(cmd->redirs);
	cmd->count = arr_length(args);
	int ret = builtin(cmd->count, args);
	dup2(0, fd[0]);
	dup2(1, fd[1]);
}

char	**prep_args(t_list *args_lst)
{
	char	**arr;
	t_list	*args;

	args = expand(args_lst);
	arr = ft_lst_to_arr(args);
	ft_lstclear(&args, do_nth);
	return (arr);
}

int	execute_simple_command(t_cmd *cmd, t_bool force_fork, t_bool wait_child)
{
	t_builtin	builtin;
	pid_t		pid;
	char		**args;
	char		*cmd_path;
	int			ret;

	args = prep_args(cmd->data.args);
	cmd->count = arr_length(args);
	builtin = get_builtin(*args);
	if (builtin && force_fork == FALSE)
	{
		ret = execute_builtin(builtin, cmd, args);
		//dup 0 1
		//prep_redirs;
		// ret = builtin(cmd->count, args);
		free_arr(args);
		//dup back 0 1
		return (ret);
	}
	pid = fork();
	if (pid)
	{
		free_arr(args);
		if (wait_child == TRUE)
		{
			int exit_status = get_exit_status(pid);
			return (exit_status);
		}
		return ((int)pid);
	}
	prep_redirs(cmd->redirs);
	cmd_path = get_cmd_path(*args);
	if (cmd_path == NULL)
		command_not_found(*args);
	if (builtin)
		exit(builtin(cmd->count, args));
	if (execve(cmd_path, args, get_env_arr()))
		perror("minishell");
	exit(126);
	return (0);
}
