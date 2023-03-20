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

t_redirections  **parse_pipe_and_redirections(char **arr, t_shell *shell)
{
	int		i;
	char	**str;
	t_redirections **tokens;

	tokens = malloc(shell->number_of_pipes + 2 * sizeof(*tokens));
	if (!tokens)
		return (NULL);
	i = -1;
	while (++i <= shell->number_of_pipes)
	{
		tokens[i] = malloc(sizeof(t_redirections));
		str = ft_split(arr[i], ' ');
		parse_redirections(str, tokens[i]);
	}
	tokens[i] = NULL;
	return (tokens);
}

void	setup_pipe_and_red(t_redirections **tokens, t_shell *shell, char **env)
{
	int		i;
	int		pid;
	char	**arr;

	create_pipes(shell->pipe1, shell->pipe2);
	i = -1;
	while (++i <= shell->number_of_pipes)
	{
		arr = copy_from_list(tokens[i]->cmds);
		pid = fork();
		if (pid == 0)
		{
			if (i < shell->number_of_pipes)
				setup_pipes_for_child(i, shell->pipe1, shell->pipe2);
			if (i == shell->number_of_pipes)
			{
				wait(NULL);
				setup_pipes_for_last_child(i, shell->pipe1, shell->pipe2);
			}
			setup_infile(tokens[i]->infile);
			setup_outfile(tokens[i]->outfile);
			setup_append(tokens[i]->append);
			execute_command(arr, env);
		}
		setup_pipes_for_next_child(i, shell->pipe1, shell->pipe2);
	}
}

void	store_line(char *line, char **env)
{
	t_redirections	redirections;
	t_shell			shell;
	t_redirections	**tokens;

	tokens = NULL;
	shell.pipes = split(line, '|');
	shell.number_of_pipes = count_pipes(shell.pipes) - 1;
	printf("shell.number_of_pipes =================| %d |\n", shell.number_of_pipes);
	if (ft_search(line, '|') && check_pipe_error(shell.pipes, line))
		parse_error();
	if (shell.pipes[0] && !ft_search(line, '|') && !contains_redirections(shell.pipes, shell.number_of_pipes))
	{
		printf("||=========================== simple cmd =========================||\n\n");
		shell.simple_cmd = ft_split(shell.pipes[0], ' ');
		run_command(&shell, env);
	}
	if (!ft_search(line, '|') && (ft_search(line, '>') || ft_search(line, '<')))
	{
		printf("||==================== redirections without pipes ================|| \n\n");
		shell.cmds = ft_split(shell.pipes[0], ' ');
		if (!valid_redirection(shell.cmds))
		{
			parse_redirections(shell.cmds, &redirections);
			setup_redirections(&redirections, &shell, env);
		}
		ft_free(shell.cmds);
	}
	if (shell.number_of_pipes > 0 && ft_search(line, '|'))
	{
		printf("||====================== pipe && redirections ====================|| \n\n");
		if (contains_redirections(shell.pipes, shell.number_of_pipes))
		{
			tokens = parse_pipe_and_redirections(shell.pipes, &shell);
			setup_pipe_and_red(tokens, &shell, env);
		}
		else if (!check_pipe_error(shell.pipes, line) && !contains_redirections(shell.pipes, shell.number_of_pipes))
			run_command(&shell, env);
	}
	if (shell.pipes)
		ft_free(shell.pipes);
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

