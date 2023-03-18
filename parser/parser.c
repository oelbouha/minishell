/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:18:59 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/10 19:23:13 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_list(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		printf("lst ==> : %s\n", temp->content);
		temp = temp->next;
	}
}

void	print(char **arr)
{
	if (!arr)
		return ;
	int i = -1;
	while (arr[++i])
		printf("arr [%d] ==> %s\n",i , arr[i]);
}

int	contains_redirections(char **arr, int i)
{
	int		j;

	j = -1;
	while (arr[++j])
	{
		if (ft_search(arr[0] , '<') || ft_search(arr[0] , '>'))
			return (1);
		if (ft_search(arr[i] , '<') || ft_search(arr[i] , '>'))
			return (1);
	}
	return (0);
}

void	setup_infile(t_list *infile)
{
	int		fd;
	t_list	*lst;

	lst = infile;
	while (lst)
	{
		fd = open(lst->content, O_RDONLY);
		if (access(lst->content, F_OK) < 0)
			print_error_msg(lst->content, ": No such file or directory", 0, 0);
		if (access(lst->content, R_OK) < 0)
			print_error_msg(lst->content, ": permission denied", 1, 0);
		dup2(fd, 0);
		close(fd);
		lst = lst->next;
	}
}

void	setup_outfile(t_list *outfile)
{
	int		fd;
	t_list	*lst;

	lst = outfile;
	while (lst)
	{
		fd = open(lst->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == - 1)
		{
			perror("minishell");
			exit(1);
		}
		dup2(fd, 1);
		close(fd);
		lst = lst->next;
	}
}

void	setup_append(t_list *append)
{
	int		fd;
	t_list	*lst;

	lst = append;
	while (lst)
	{
		
		fd = open(lst->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == - 1)
		{
			perror("minishell: outfile");
			exit(1);
		}
		dup2(fd, 1);
		close(fd);
		lst = lst->next;
	}
}

// void	setup_here_doc(t_list *here_doc)
// {
// 	int		fd;

// 	while (here_doc)
// 	{
// 		fd = open(append, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == - 1)
// 		{
// 			perror("minishell");
// 			exit(1);
// 		}
// 		dup2(fd, 1);
// 	}
// }

void	store_line(char *line, char **env)
{
	t_redirections	redirections;
	t_shell			shell;

	shell.pipes = split(line, '|');
	shell.number_of_pipes = count_pipes(shell.pipes) - 1;
	if (ft_search(line, '|') && check_pipe_error(shell.pipes, line))
		parse_error();
	if (!ft_search(line, '|') && !contains_redirections(shell.pipes, shell.number_of_pipes))
	{
		printf("++++++++ simple cmd +++++++++\n");
		shell.simple_cmd = ft_split(shell.pipes[0], ' ');
		ft_free(shell.pipes);
		run_command(&shell, env);
	}
	else if (!ft_search(line, '|') && (ft_search(line, '>') || ft_search(line, '<')))
	{
		printf("++++++++ redirections without pipes +++++++++\n");
		shell.cmds = ft_split(shell.pipes[0], ' ');
		ft_free(shell.pipes);
		if (!valid_redirection(shell.cmds))
		{
			parse_redirections(shell.cmds, &redirections);
			// printf("====== cmds ======\n");
			// print_list(redirections.cmds);
			// printf("====== outfile ======\n");
			// print_list(redirections.outfile);
			// printf("================================\n");
			setup_redirections(&redirections, &shell, env);
		}
	}
	if (shell.number_of_pipes > 0)
	{
		printf("++++++++ pipe && redirections +++++++++\n");
		if (contains_redirections(shell.pipes, shell.number_of_pipes))
		{
			printf("hnaya\n");
		}
		else if (!check_pipe_error(shell.pipes, line) && !contains_redirections(shell.pipes, shell.number_of_pipes))
			run_command(&shell, env);
	}
	free(line);
}

void	read_input(char **env)
{
	char	*line;

	while (1)
	{
		line = readline("");
		store_line(line, env);
	}
}

