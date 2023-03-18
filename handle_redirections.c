/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:52:11 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/16 12:52:15 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	setup_infile_and_heredoc(char *str, t_redirections *red, char *word)
// {
// 	if (setup_infile_redirection(str, red, word))
// 		return (1);
// 	if (setup_heredoc(str, red, word))
// 		return (1);
// 	return (0);
// }

// int	setup_trunc_and_append_file(char *str, t_redirections *red, char *word)
// {
// 	if (setup_append_file(str, red, word))
// 		return (1);
// 	if (setup_trunc_file(str, red, word))
// 		return (1);
// 	return (0);
// }

char	*ft_strcpy(char *str, t_redirections *red)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	new_str = malloc(i  + 1);
	if (!new_str)
		return (NULL);
	j = -1;
	while (++j < i)
		new_str[j] = str[j];
	red->index = j;
	new_str[j] = '\0';
	return (new_str);
}

void	parsing_redirection(char *str, t_redirections *red)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<')
		{
			i += 1;
			ft_lstadd_back(&red->infile, ft_lstnew(ft_strcpy(&str[i], red)));
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			ft_lstadd_back(&red->here_doc_delimiter, ft_lstnew(ft_strcpy(&str[i], red)));
		}
		else if (str[i] == '>' && str[i + 1] != '>')
		{
			i += 1;
			ft_lstadd_back(&red->outfile, ft_lstnew(ft_strcpy(&str[i], red)));
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			i += 2;
			ft_lstadd_back(&red->append, ft_lstnew(ft_strcpy(&str[i], red)));
		}
		else
			ft_lstadd_back(&red->cmds, ft_lstnew(ft_strcpy(&str[i], red)));
		i += red->index;
	}
}

int	not_a_command(char *s)
{
	char	*path;

	path = make_path(s);
	if (path)
	{
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

void	parse_redirections(char **arr, t_redirections *red)
{
	int		i;

	i = 0;
	red->append = NULL;
	red->cmds = NULL;
	red->outfile = NULL;
	red->infile = NULL;
	red->here_doc_delimiter = NULL;
	while(arr[i])
	{
		if (ft_strcmp(arr[i], "<") == 0)
			while(arr[++i] && !ft_search(arr[i], '<') && !ft_search(arr[i], '>') && not_a_command(arr[i]))
				ft_lstadd_back(&red->infile, ft_lstnew(arr[i]));
		else if (ft_strcmp(arr[i], "<<") == 0)
			while(arr[++i] && !ft_search(arr[i], '<') && !ft_search(arr[i], '>') && not_a_command(arr[i]))
				ft_lstadd_back(&red->here_doc_delimiter, ft_lstnew(arr[i]));
		else if (ft_strcmp(arr[i], ">") == 0)
			while(arr[++i] && !ft_search(arr[i], '<') && !ft_search(arr[i], '>') && not_a_command(arr[i]))
				ft_lstadd_back(&red->outfile , ft_lstnew(arr[i]));
		else if (ft_strcmp(arr[i], ">>") == 0)
			while(arr[++i] && !ft_search(arr[i], '<') && !ft_search(arr[i], '>') && not_a_command(arr[i]))
				ft_lstadd_back(&red->append, ft_lstnew(arr[i]));
		else if ((ft_search(arr[i], '<') || ft_search(arr[i], '>'))
				&& (ft_strcmp(arr[i], ">") || ft_strcmp(arr[i], ">>")
				||	(ft_strcmp(arr[i], "<") || ft_strcmp(arr[i], "<<"))))
		{
			parsing_redirection(arr[i], red);
			i++;
		}
		else
		{
			ft_lstadd_back(&red->cmds, ft_lstnew(arr[i]));
			i++;
		}
	}
}


int	check_redirection(char *s, char *next_arg)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] == '>' && (s[i + 1] == '<' || s[i + 1] == '|'))
			|| (s[i] == '<' && (s[i + 1] == '>' || s[i + 1] == '|')))
				return (1);
		else if ((s[i] == '>' || s[i] == '<')
			&& (s[i + 1] == '#'))
				return (1);
		else if ((s[i] == '>' && s[i + 1] != '>' && !s[i + 1]) && !next_arg)
				return (1);
		else if ((s[i] == '<' && s[i + 1] != '<' && !s[i + 1]) && !next_arg)
				return (1);
	}
	return (0);
}


int	count_redirections(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (1);
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (1);
	}
	return (0);
}

int	valid_redirection(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((ft_strcmp(str[i], "<<") == 0 || ft_strcmp(str[i], ">>") == 0
			|| ft_strcmp(str[i], "<") == 0
			|| ft_strcmp(str[i], ">") == 0) && !str[i + 1])
		{
			parse_error();
			return (1);
		}
		if (check_redirection(str[i], str[i + 1]) || count_redirections(str[i]))
		{
			parse_error();
			return (1);
		}
	}
	return (0);
}

void	setup_redirections(t_redirections *red, t_shell *shell, char **env)
{
	int		pid;
	int		i;
	char	**arr;
	t_list *temp;

	temp = red->cmds;
	arr = NULL;
	if (ft_lstsize(temp))
	{
		arr = malloc(ft_lstsize(temp) + 1);
		if (!arr)
			return ;
		i = 0;
		while(temp)
		{
			arr[i++] = temp->content;
			temp = temp->next;
		}
		arr[i] = NULL;
	}
	print(arr);
	pid = fork();
	if (pid == 0)
	{
		setup_infile(red->infile);
		setup_outfile(red->outfile);
		setup_append(red->append);
		if (arr[0])
			execute_command(arr, env);
	}
	if (pid > 0)
	{
		wait(NULL);
		free_lst(red->append);
		free_lst(red->outfile);
		free_lst(red->infile);
		free_lst(red->here_doc_delimiter);
		if (arr)
			free(arr);
		free_lst(red->cmds);
		ft_free(shell->cmds);
	}
}