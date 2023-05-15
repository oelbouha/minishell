

#include "executer.h"

int	needs_spliting(char *str)
{
	if (ft_strchr(str, '"') || ft_strchr(str, '\'') || !should_expand_var(str))
		return (0);
	else
		return (1);
}

char	*modify_expanded_spaces(char *expanded)
{
	char	*modified;
	char	next_char;
	int		i;
	int		j;

	modified = malloc(ft_strlen(expanded) + 1);
	if (!modified)
		return (NULL);
	i = 0;
	j = 0;
	while (expanded[i])
	{
		if (expanded[i] == ' ' || expanded[i] == '\t')
		{
			next_char = expanded[i++];
			modified[j++] = ' ';
			while (expanded[i] == next_char)
				i++;
		}
		else
			modified[j++] = expanded[i++];
	}
	modified[j] = '\0';
	return (modified);
}

int	should_expand_var(char *str)
{
	char	next_quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			next_quote = str[i];
			i++;
			while (str[i] && str[i] != next_quote)
				i++;
			i++;
		}
		else if (str[i] == '$')
			return (1);
		else
			i++;
	}
	return (0);
}

t_list	*split_var(char *expanded)
{
	t_list	*new_lst;
	t_list	*node;
	char	**arr;
	char	*modified;

	new_lst = NULL;
	modified = modify_expanded_spaces(expanded);
	free(expanded);
	arr = ft_split(modified, ' ');
	free(modified);
	if (arr == NULL)
		return (NULL);
	int i = -1;
	while (arr[++i])
	{
		node =  ft_lstnew(arr[i]);
		if (node == NULL)
			return (ft_lstclear(&new_lst, free), NULL);
		ft_lstadd_back(&new_lst, node);
	}
	free(arr);
	return (new_lst);
}

void	join_prev_with_newlst(t_list **prv, t_list **lst, t_list **newlst)
{
	t_list	*last;
	char	*str;

	last = ft_lstlast(*newlst);
	str = (*prv)->content;
	(*prv)->content = ft_strjoin((*prv)->content, (*newlst)->content);
	free(str);
	ft_lstdel_first(lst, free);
	last->next = *lst;
	ft_lstdel_first(newlst, free);
	(*prv)->next = *newlst;
	*lst = last->next;
	*prv = last;
}

void	expand_var_ad_join(t_list **prv, t_list **lst, t_list **tmp, char *str)
{
	t_list	*last;
	t_list	*newlst;

	newlst = split_var(str);
	last = ft_lstlast(newlst);
	if (*prv)
		join_prev_with_newlst(prv, lst, &newlst);
	else
	{
		*prv = newlst;
		last->next = (*lst)->next;
		ft_lstdel_first(lst, free);
		*lst = last->next;
		*tmp = *prv;
		*prv = last;
	}
}

void	rm_quotes_and_expand(t_list **prev, t_list **lst, t_list **new_lst)
{
	char	*str;

	if (should_expand_var((*lst)->content))
	{
		(*lst)->content = remove_quotes((*lst)->content);
		str = (*lst)->content;
		(*lst)->content = expand_var((*lst)->content);
		free(str);
	}
	else
		(*lst)->content = remove_quotes((*lst)->content);
	if (*prev)
	{
		str = (*prev)->content;
		(*prev)->content = ft_strjoin((*prev)->content, (*lst)->content);
		free(str);
		ft_lstdel_first(lst, free);
		(*prev)->next = *lst;
		*lst = (*prev)->next;
	}
	else
	{
		*prev = *lst;
		*lst = (*lst)->next;
		*new_lst = *prev;
	}
}

void	not_a_valid_var(t_list **lst, t_list **prev, char *expanded)
{
	ft_lstdel_first(lst, free);
	free(expanded);
	if (*prev)
		(*prev)->next = *lst;
}

t_list	*split_and_join(t_list *lst)
{
	t_list	*new_lst;
	t_list	*prev;
	char	*expanded;

	prev = NULL;
	new_lst = EMPTY_LST;
	while (lst && new_lst)
	{
		if (needs_spliting(lst->content))
		{
			expanded = expand_var(lst->content);
			if (*expanded == 0)
				not_a_valid_var(&lst, &prev, expanded);
			else
				expand_var_ad_join(&prev,  &lst, &new_lst, expanded);
		}
		else
			rm_quotes_and_expand(&prev, &lst, &new_lst);
	}
	return (new_lst);
}

t_list	*expand(t_list *cur, t_list *prev, t_list **lst_ptr)
{
	t_list	*lst;
	t_list	*temp;

	lst = split_content(cur->content);
	lst = split_and_join(lst);
	if (lst == EMPTY_LST)
	{
		ft_lstdel_first(&cur, free);
		if (prev)
			prev->next = cur;
		return (prev);
	}
	if (prev)
	{
		temp = cur->next;
		prev->next = lst;
	}
	else
	{
		*lst_ptr = lst;
		temp = cur->next;
	}
	prev = ft_lstlast(lst);
	prev->next = temp;
	return (ft_lstdel_first(&cur, free), prev);
}

t_list	*split_expanded(t_list *lst)
{
	t_list	*cur;
	t_list	*prev;

	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (should_expand_var(cur->content))
		{
			prev = expand(cur, prev, &lst);
			if (prev == NULL)
				return (NULL);
			cur = prev->next;
		}
		else
		{
			cur->content = remove_quotes(cur->content);
			prev = cur;
			cur = cur->next;
		}
	}
	return (lst);
}