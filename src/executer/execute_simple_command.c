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

void	print_arr(char **arr)
{
	if (!arr)
		return ;
	for (int i = 0; arr[i]; i++)
		printf("arr[%d]: %s\n", i, arr[i]);
}

void	prep_redirs(t_list *redirs)
{
	(void)redirs;
	return;
}

char	**prep_args(t_list **args_lst)
{
	t_list	*args;

	args = get_expanded(*args_lst);
	*args_lst = args;
	// print(args);
	return (ft_lst_to_arr(args));
}

int	is_builtind(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}


int	execute_simple_command(t_cmd *cmd, t_bool force_fork, t_bool wait_child)
{
	t_builtin	builtin;
	pid_t		pid;
	char		**args;
	char		*cmd_path;
	int			ret;

	args = prep_args(&cmd->data._simple.args);
	if (args == NULL || *args == NULL)
		return (free (args), 0);
	builtin = get_builtin(*args);
	cmd->count = arr_length(args);
	if (builtin && force_fork == FALSE)
	{
		ret = builtin(cmd->count, args);
		free (args);
		return (ret);
	}
	pid = fork();
	if (pid)
	{
		// CLOSE PIPE_IN;
		if (wait_child == TRUE)
		{
			printf("waiting... \n");
			return (free(args), get_exit_status(pid));
		}
		return (free(args), 0);
	}
	prep_redirs(cmd->redirs);
	cmd_path = get_cmd_path(*args);
	if (cmd_path == NULL)
		command_not_found(args[0]);
	if (builtin)
		exit(builtin(cmd->count, args));
	if (execve(cmd_path, args, get_env_arr()))
		return (perror("minishell"), exit(126), 0);
	return (0);
}
