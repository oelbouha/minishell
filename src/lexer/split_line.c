/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:16:08 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/13 14:13:08 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*remove_last_node(t_list **lst)
{
	t_list	*cur;

	if (lst == NULL)
		return (NULL);
	cur = *lst;
	if (cur->next == NULL)
	{
		free(cur->content);
		free(cur);
		*lst = NULL;
		return (NULL);
	}
	while (cur->next->next)
		cur = cur->next;
	free(cur->next->content);
	free(cur->next);
	cur->next = NULL;
	return (cur);
}

void	print(t_list *lst)
{
	int		i;

	if (!lst)
		return ;
	i = 1;
	printf("\n");
	while (lst)
	{
		printf("[%2d]: %s\n",i++, lst->content);
		lst = lst->next;
	}
}

int	get_token_len(char *line)
{
	int	len;

	len = 0;
	if (BONUS && (!ft_strncmp(line, "||", 2) || !ft_strncmp(line, "&&", 2)))
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

char	*get_token(char *str, int *err)
{
	char	*token;
	int		len;

	len = get_token_len(str);
	if (len == 0)
		return (NULL);
	token = ft_substr(str, 0, len);
	if (!token)
		*err = 1;
	return (token);
}

int	cant_be_last(char *token)
{
	return (ft_templatecmp(token, "<<:>>:>:|:<", ':')
		|| (BONUS && ft_templatecmp(token, "||:&&:(", ':')));
}


int analyse_last_node(t_list *lst)
{
	t_list	*last;

	if (!lst)
		return (0);
	last = ft_lstlast(lst);
	if (cant_be_last(last->content))
		msh_err("syntax error near unexpected token", last->content);
	else
		return (0);
	while (last && cant_be_last(last->content))
		last = remove_last_node(&lst);
	return (1);
}

t_list	*split_line(char *line)
{
	t_list	*lst;
	char	*token;
	int		error;

	error = 0;
	lst = NULL;
	while (*line)
	{
		while (*line && (*line == SPACE || *line == TAB))
			line++;
		token = get_token(line, &error);
		if (error == 1)
			return (ft_lstclear(&lst, free), NULL);
		else if (analyze_syntax(lst, token))
		{
			free(token);
			break ;
		}
		push_token_to_list(&lst, token, &error);
		line += ft_strlen(token);
	}
	if (analyse_last_node(lst))
		return (lst);
	return (lst);
}

