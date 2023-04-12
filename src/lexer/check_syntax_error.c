/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:24:14 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/10 13:24:16 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lexer.h"

int	is_redir(char *token)
{
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
	|| ft_strcmp(token, "<<") == 0 || ft_strcmp(token, "<") == 0)
		return (1);
	return (0);
}

int	is_simple_word(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (ft_strchr("><|", token[i]))
			return (1);
	}
	return (0);
}

int	is_simple_word(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (is_redir(token) || !ft_strcmp(token, ")")
		|| !ft_strcmp(token, "(") || !ft_strcmp(token, "|"))
			return (1);
	}
	return (0);
}

void	pipe_errors(t_list *lst, char *token, int *error)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (!lst)
	{
		print_error_msg(token);
		*error = 1;
	}
	if (node)
	{
		if (is_redir(node->content) || !ft_strcmp(node->content, "(")
		|| !ft_strcmp(node->content, ")") || is_and_or(node->content))
		{
			print_error_msg(token);
			*error = 1;
		}
	}
}

void	and_or_errors(t_list *lst, char *token, int *error)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (!lst)
	{
		print_error_msg(token);
		*error = 1;
	}
	if (node)
	{
		if (!ft_strcmp(node->content, "(") || is_redir(node->content)
			|| is_and_or(node->content) || !ft_strcmp(node->content, "|"))
		{
			print_error_msg(token);
			*error = 1;
		}
	}
}

void	open_parentheses_errors(t_list *lst, char *token, int *error)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (node)
	{
		if (!ft_strcmp(node->content, ")") || is_redir(node->content))
		{
			print_error_msg(token);
			*error = 1;
		}
	}
}

void	closed_parentheses_errors(t_list *lst, char *token, int *error)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (!lst)
	{
		print_error_msg(token);
		*error = 1;
	}
	if (node)
	{
		if (!ft_strcmp(node->content, "|") || !ft_strcmp(node->content, "(")
			|| is_and_or(node->content) || is_redir(node->content))
		{
			print_error_msg(token);
			*error = 1;
		}
	}
}

void	redir_errors(t_list *lst, char *token, int *error)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (node)
	{
		if (is_redir(node->content))
		{
			print_error_msg(token);
			*error = 1;
		}
	}
}

void	simple_word_errors(t_list *lst, char *token, int *error)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (node)
	{
		if (!ft_strcmp(node->content, ")")) /*|| !ft_strcmp(node->content, "(")*/
		{
			print_error_msg(token);
			*error = 1;
		}
	}
}

int	check_syntax_error(t_list *lst, char *token)
{
	int	err;

	if (!token)
		return (1);
	err = 0;
	if (ft_strcmp(token, "|") == 0)
		pipe_errors(lst, token, &err);
	if (is_redir(token))
		redir_errors(lst, token, &err);
	if (BONUS && is_and_or(token))
		and_or_errors(lst, token, &err);
	if (BONUS && ft_strcmp(token, "(") == 0)
		open_parentheses_errors(lst, token, &err);
	if (BONUS && ft_strcmp(token, ")") == 0)
		closed_parentheses_errors(lst, token, &err);
	else
		simple_word_errors(lst, token, &err);
	if (err == 1)
		return (1);
	return (0);
}