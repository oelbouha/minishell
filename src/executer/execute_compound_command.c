/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_compound_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:53:49 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 13:22:32 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

typedef struct s_pipe_redirs
{
	int	in;
	int	out;
	int	unused;
}	t_pipe_redirs;

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

void	close_pipe(int p[2])
{
	if (p[0] > -1)
	{
		ft_printf("closing fd:%d\n", p[0]);
		close(p[0]);
	}
	if (p[1] > -1)
	{
		ft_printf("closing fd:%d\n", p[1]);
		close(p[1]);
	}	
}

t_pipe_redirs	create_pipes(int p1[2], int p2[2], int count, int i)
{
	if (i == 0)
	{
		ft_memset(p1, -1, 2 * sizeof(int));
		ft_memset(p2, -1, 2 * sizeof(int));
	}
	if (i % 2 == 0)
	{
		if (i == count - 1)
			return ((t_pipe_redirs){.in = p2[0], .out = -1, .unused = -1});
		else if (pipe(p1) == 0)
			return ((t_pipe_redirs){.in = p2[0], .out = p1[1], .unused = p1[0]});
	}
	else if (count > 1)
	{
		if (i == count - 1)
			return ((t_pipe_redirs){.in = p1[0], .out = -1, .unused = -1});
		if (pipe(p2) == 0)
			return ((t_pipe_redirs){.in = p1[0], .out = p2[1], .unused = p2[0]});
	}
	perror("-minishell");
	close_pipe(p1);
	close_pipe(p2);
	return ((t_pipe_redirs){.in = -1, .out = -1, .unused = -1});
}

int	execute_compound_command(t_cmd *cmd)
{
	pid_t			child_pid;
	int				status;
	t_cmd			*command;
	int				pipe1[2];
	int				pipe2[2];
	t_pipe_redirs	p_redirs;
	int				i;

	i = -1;
	while (++i < cmd->count)
	{
		p_redirs = create_pipes(pipe1, pipe2, cmd->count, i);
		command = cmd->data.arr[i]->content;
		if (p_redirs.in != -1 || p_redirs.out != -1)
			add_pipe_redirs(&command->redirs, p_redirs);
		child_pid = execute_simple_command(command, TRUE, FALSE);
		close(p_redirs.in);
		close(p_redirs.out);
	}
	status = get_exit_status(child_pid);
	while (waitpid(-1, &i, 0) != -1)
		;
	return (status);
}
