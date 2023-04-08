/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:16:08 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/08 14:07:02 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	z(char *s)
{
	ft_printf("%s\n", s);
}

void	print(t_list *lst)
{
	t_list *temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		printf("token ===> %s\n",temp->content);
		temp =temp->next;
	}
}

int	handle_parenthesis(t_list **lst, char *str, int *err)
{
	char	*token;

	token = ft_substr(str, 0, 1);
	if (!token)
	{
		*err = 1;
		return (1);
	}
	ft_lstadd_back(lst, ft_lstnew(token));
	return (1);
}

int	and_or_handler(t_list **lst, char *str, int *err)
{
	char	*token;

	token = ft_substr(str, 0, 2);
	if (!token)
	{
		*err = 1;
		return (1);
	}
	ft_lstadd_back(lst, ft_lstnew(token));
	return (2);
}

t_list	*split_line_to_tokens(t_lexer *lexer, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == SPACE || s[i] == TAB)
			i++;
		else if (BONUS
			&& (!ft_strncmp(&s[i], "||", 2) || !ft_strncmp(&s[i], "&&", 2)))
			i += and_or_handler(&lexer->lst, &s[i], &lexer->error);
		else if (BONUS && (s[i] == '(' || s[i] == ')'))
			i += handle_parenthesis(&lexer->lst, &s[i], &lexer->error);
		else if (s[i] == SINGLE_QUOTE || s[i] == DOUBLE_QUOTE)
			i += handle_quotes(&lexer->lst, &s[i], &lexer->error);
		else if (s[i] == '>' || s[i] == '<' || s[i] == '|')
			i += handle_redir_and_pipe(&lexer->lst, &s[i], &lexer->error);
		else
			i += simple_word(&lexer->lst, &s[i], &lexer->error);
		if (lexer->error == 1)
		{
			ft_lstclear(&lexer->lst, free_lst_content);
			return (NULL);
		}
	}
	return (lexer->lst);
}

t_list	*split_line(char *line)
{
	t_lexer lexer;

	lexer.lst = NULL;
	lexer.error = 0;
	return (split_line_to_tokens(&lexer, line));
}

