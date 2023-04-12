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
	while (temp)
	{
		printf("token ===> %s\n",temp->content);
		temp =temp->next;
	}
}

char	*create_token(char *str, int *err, int len)
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

int check_last_node(t_list *lst)
{
	t_list	*node;

	if (!lst)
		return (0);
	node = ft_lstlast(lst);
	if (!ft_strcmp(node->content, "|") || is_redir(node->content)
		|| (BONUS && (is_and_or(node->content)
		|| !ft_strcmp(node->content, "("))))
	{
		print_error_msg(node->content);
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
		token = create_token(&line[i], &error, len);
		if (check_syntax_error(lst, token))
		{
			free(token);
			ft_lstclear(&lst, free);
			return (NULL);
		}
		push_token_to_list(&lst, token, &error);
		if (error == 1)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		i += len;
	}
	if (check_last_node(lst))
	{
		ft_lstclear(&lst, free);
		return (NULL);
	}
	return (lst);
}

/*

// line full of spaces  [node->content = NULL]
// failed allocation	[NULL]

t_list *token;
loop(*line)
{
	token = get_token(...); // if null error
	if (token == NULL)
		return (ft_lstclear(&list), NULL);
	else if ()
	
}



loop
{
	list = lexer(&err);
	tree = parse(list);
	if (err == 0)
		execute(tree);
	free(tree)
}


*/