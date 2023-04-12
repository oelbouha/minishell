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

void	remove_last_node(t_list	**lst)
{
	t_list	*last_node;
	t_list	*temp;
	t_list	*list;

	temp = *lst;
	list = temp;
	last_node = ft_lstlast(*lst);
	while (ft_strcmp(temp->next->content, last_node->content))
		temp = temp->next;
	temp->next = NULL;
	*lst = list;
}

void	print(t_list *lst)
{
	t_list *temp;

	if (!lst)
		return ;
	temp = lst;
	printf("\n");
	while (temp)
	{
		printf("token ===> %s\n",temp->content);
		temp =temp->next;
	}
}

char	*get_token(char *str, int *err, int len)
{
	char	*token;

	if (len == 0)
		return (NULL);
	token = ft_substr(str, 0, len);
	if (!token)
	{
		*err = 1;
		return (0);
	}
	return (token);
}

int	token_lenght(char *line)
{
	int	len;

	len = 0;
	if (BONUS && is_and_or(line))
		len = 2;
	else if (BONUS && (line[0] == '(' || line[0] == ')'))
		len = 1;
	else if (line[0] == '\''|| line[0] == '"')
		len = handle_quotes(line);
	else if (line[0] == '>' || line[0] == '<' || line[0] == '|')
		len = handle_redir_and_pipe(line);
	else
		len = simple_word(line);
	return (len);
}

int analyse_last_node(t_list *lst)
{
	t_list	*node;

	if (!lst)
		return (0);
	node = ft_lstlast(lst);
	if (cmp(node->content, "|:<<:<:>>:>") || (BONUS && (is_and_or(node->content)
		|| !ft_strcmp(node->content, "("))))
	{
		msh_err("syntax error near unexpected token", node->content);
		return (1);
	}
	return (0);
}

t_list	*split_line(char *line)
{
	t_list	*lst;
	char	*token;
	int		error;
	int		i;
	int		len;

	i = 0;
	len = 0;
	error = 0;
	lst = NULL;
	while (line[i])
	{
		while (line[i] && (line[i] == SPACE || line[i] == TAB))
			i++;
		len = token_lenght(&line[i]);
		token = get_token(&line[i], &error, len);
		if (analyze_syntax(lst, token))
		{
			free(token);
			return (lst);
		}
		push_token_to_list(&lst, token, &error);
		if (error == 1)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		i += len;
	}
	if (analyse_last_node(lst))
		return (lst);
	return (lst);
}

