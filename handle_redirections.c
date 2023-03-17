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

void	parsing_infile_and_heredoc(char *str, t_redirections *red)
{
	int 	i;

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
		i += red->index;
	}
}

int	setup_infile_and_heredoc(char *str, t_redirections *red, char *word)
{
	if (ft_strcmp(str, "<") == 0)
		ft_lstadd_back(&red->infile, ft_lstnew(word));
	if (ft_strcmp(str, "<<") == 0)
		ft_lstadd_back(&red->here_doc_delimiter, ft_lstnew(word));
	else if (ft_search(str, '<') && (ft_strcmp(str, "<") || ft_strcmp(str, "<<")))
		parsing_infile_and_heredoc(str, red);
	return (0);
}

/*
int	setup_heredoc(char *str, t_redirections *red, char *word)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strcmp(str, "<<") == 0)
		{
			if (word)
				red->here_doc_delimiter = word;
			else
				return (1);
		}
		else if (ft_search(str, '<') && ft_search(&str[i + 1], '<'))
		{
			red->here_doc_delimiter = ft_strrchr(str, '<');
			if (!red->here_doc_delimiter)
				return (1);
		}
	}
	return (0);
}


int	setup_trunc_file(char *str, t_redirections *red, char *word)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (ft_strcmp(str, ">") == 0)
		{
			if (word)
				red->infile = word;
			else
				return (1);
		}
		else if (ft_search(str, '>') && !ft_search(&str[i + 1], '>'))
		{
			red->infile = ft_search(str, '>');
			if (!red->infile)
				return (1);
		}
	}
	return (0);
}

int	setup_append_file(char *str, t_redirections *red, char *word)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strcmp(str, ">>") == 0)
		{
			if (word)
				red->here_doc_delimiter = word;
			else
				return (1);
		}
		else if (ft_search(str, '>') && ft_search(&str[i + 1], '>'))
		{
			red->here_doc_delimiter = ft_strrchr(str, '>');
			if (!red->here_doc_delimiter)
				return (1);
		}
	}
	return (0);
}
*/
void	setup_redirections(char **arr, t_redirections *redirections)
{
	int		ret;
	int		i;

	i = -1;
	redirections->append = NULL;
	redirections->outfile = NULL;
	redirections->infile = NULL;
	redirections->here_doc_delimiter = NULL;
	while(arr[++i])
	{
		if (ft_search(arr[i], '<'))
		{
			ret = setup_infile_and_heredoc(arr[i], redirections, arr[i + 1]);
			if (ret)
				parse_error();
		}
		// if (ft_search(arr[i], '>'))
		// {
		// 	ret = setup_trunc_and_append_file(arr[i], redirections, arr[i + 1]);
		// 	if (ret)
		// 		parse_error();
		// }
	}
}

int	check_redirection(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '>' && (str[i + 1] == '<' || str[i + 1] == '|'))
			|| (str[i] == '<' && (str[i + 1] == '>' || str[i + 1] == '|')))
				return (1);
		else if ((str[i] == '>' || str[i] == '<')
			&& (str[i + 1] == '#'))
				return (1);
	}
	return (0);
}

// int	check_here_doc(char *str)
// {
// 	int		i;
// 	int		count;

// 	if (!str)
// 		return (0);
// 	i = -1;
// 	count = 0;
// 	while (str[++i])
// 	{
// 		if (str[i] == '|' || str[0] == '#')
// 		{
// 			parse_error();
// 			return (1);
// 		}
// 		if (str[i] == '>' || str[i] == '<')
// 			count++;
// 	}
// 	return (0);
// }

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
		if (check_redirection(str[i]) || count_redirections(str[i]))
		{
			parse_error();
			return (1);
		}
	}
	return (0);
}
