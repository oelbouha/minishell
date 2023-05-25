/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_compound_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:53:49 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/25 12:25:40 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	add_pipe_redir(t_list **redirs, int fd, t_redir_type type)
{
	t_list	*redir_node;
	t_redir	*redir;

	redir_node = ft_calloc(1, sizeof(t_list));
	if (redir_node == NULL)
		return (1);
	redir = malloc(sizeof(t_redir));
	if (redir == NULL)
		return (free(redir_node), 1);
	redir->type = type;
	redir->to.fd.val = fd;
	redir_node->content = redir;
	ft_lstadd_front(redirs, redir_node);
	return (0);
}

int	add_pipe_redirs(t_list **redirs, t_pipe_redirs pipes)
{
	if (*redirs == NO_REDIRS)
		*redirs = NULL;
	if (pipes.in > 0)
		add_pipe_redir(redirs, pipes.in, PIPE_IN);
	if (pipes.out > 0)
		add_pipe_redir(redirs, pipes.out, PIPE_OUT);
	if (pipes.unused > 0)
		add_pipe_redir(redirs, pipes.unused, PIPE_UNUSED);
	return (0);
}

t_pipe_redirs	create_pipes(int p1[2], int p2[2], int count, int i)
{
	if (i % 2 == 0)
	{
		if (i == count - 1)
			return ((t_pipe_redirs){.in = p2[0], .out = -1, .unused = -1});
		else if (pipe(p1) == 0)
			return ((t_pipe_redirs){.in = p2[0], .out = p1[1],
				.unused = p1[0]});
	}
	else if (count > 1)
	{
		if (i == count - 1)
			return ((t_pipe_redirs){.in = p1[0], .out = -1, .unused = -1});
		if (pipe(p2) == 0)
			return ((t_pipe_redirs){.in = p1[0], .out = p2[1],
				.unused = p2[0]});
	}
	perror("minishell");
	close(p1[0]);
	close(p1[1]);
	close(p2[0]);
	close(p2[1]);
	return ((t_pipe_redirs){.in = -1, .out = -1, .unused = -1});
}

int	execute_piped_command(t_cmd *cmd, int i, int *p1, int *p2)
{
	pid_t			child_pid;
	t_pipe_redirs	p_redirs;
	t_cmd			*command;

	p_redirs = create_pipes(p1, p2, cmd->count, i);
	command = cmd->data.arr[i]->content;
	if (p_redirs.in != -1 || p_redirs.out != -1)
		add_pipe_redirs(&command->redirs, p_redirs);
	child_pid = execute_command(command, TRUE, FALSE);
	close(p_redirs.in);
	close(p_redirs.out);
	return (child_pid);
}

int	execute_compound_command(t_cmd *cmd)
{
	pid_t			child_pid;
	int				status;
	int				pipe1[2];
	int				pipe2[2];
	int				i;

	ft_memset(pipe1, -1, 2 * sizeof(int));
	ft_memset(pipe2, -1, 2 * sizeof(int));
	i = -1;
	while (++i < cmd->count)
		child_pid = execute_piped_command(cmd, i, pipe1, pipe2);
	status = get_exit_status(child_pid);
	while (waitpid(-1, &i, 0) != -1)
		;
	return (status);
}
