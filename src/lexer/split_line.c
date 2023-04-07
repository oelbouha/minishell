/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:16:08 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/07 17:16:18 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	word_len(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '>' || str[i] == '<'
			|| str[i] == '|' || str[i] == 34 || str[i] == 39)
			return (i);
	}
	return (i);
}

int	handle_quotes(t_list **lst, char *str, int *err)
{
	char	*token;
	char	next_quote;
	int		i;

	i = 0;
	next_quote = str[i];
	i++;
	while (str[i] && str[i] != next_quote)
		i++;
	i++;
	token = ft_substr(str, 0, i);
	if (!token)
		*err = 1;
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i);
}

int	handle_redir(t_list **lst, char *str, int *err)
{
	char	*token;
	char	next_char;
	int		i;

	i = 0;
	next_char = str[i];
	while (str[i] && str[i] == next_char)
		i++;
	token = ft_substr(str, 0, i);
	if (!token)
		*err = 1;
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i);
}

int	handle_pipe(t_list **lst, char *str, int *err)
{
	char	*token;
	char	next_char;
	int		i;

	i = 0;
	next_char = str[i];
	while (str[i] && str[i] == next_char)
		i++;
	token = ft_substr(str, 0, i);
	if (!token)
		*err = 1;
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i);
}

int	simple_word(t_list **lst, char *str, int *err)
{
	char	*token;
	int		i;

	i = word_len(str);
	token = ft_substr(str, 0, i);
	if (!token)
		*err = 1;
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i);
}

void	print(t_list *lst)
{
	t_list *temp;

	temp = lst;
	while (temp)
	{
		printf("token |===> %s\n",temp->content);
		temp =temp->next;
	}
}

t_list	*split_line(char *line)
{
	t_list	*lst;
	int		err;
	int		i;

	i = 0;
	err = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == 34 || line[i] == 39)
			i += handle_quotes(&lst, &line[i], &err);
		else if (line[i] == '>' || line[i] == '<')
			i += handle_redir(&lst, &line[i], &err);
		else if (line[i] == '|')
			i += handle_pipe(&lst, &line[i], &err);
		// else if ((line[i] == '|' && line[i + 1] == '|') || )
		// 	i += or_and_handler(&lst, &line[i], &err);
		else
			i += simple_word(&lst, &line[i], &err);
		if (err == 1)
		{
			// free and return 
		}
	}
	print(lst);
	return (lst);
}

