/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:51:57 by ysalmi            #+#    #+#             */
/*   Updated: 2023/03/24 22:04:12 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"

t_keyvalue	*new_keyvalue(char *key, char *value)
{
	t_keyvalue	*kv;

	kv = malloc(sizeof(t_keyvalue));
	if (kv == NULL)
		return (NULL);
	kv->key = key;
	kv->value = value;
	return (kv);
}

void	destroy_keyvalue(t_keyvalue *kv)
{
	if (kv)
	{
		free(kv->key);
		free(kv);
	}
}

t_list	*new_dictionary(char **arr, char sep)
{
	t_list		*dict;
	t_keyvalue	*kv;
	t_list		*node;
	int			i;

	dict = NULL;
	i = -1;
	while (arr && arr[++i])
	{
		kv = new_keyvalue(NULL, NULL);
		if (kv == NULL)
			return (ft_lstclear(&dict, (t_lstdel)destroy_keyvalue), NULL);
		kv->key = ft_strdup(arr[i]);
		if (kv->key == NULL)
			return (ft_lstclear(&dict, (t_lstdel)destroy_keyvalue),
				free(kv), NULL);
		kv->value = ft_strchr(kv->key, sep) + 1;
		kv->key[kv->value - kv->key - 1] = 0;
		node = ft_lstnew(kv);
		if (node == NULL)
			return (ft_lstclear(&dict, (t_lstdel)destroy_keyvalue),
				free(kv), NULL);
		ft_lstadd_back(&dict, node);
	}
	return (dict);
}

t_keyvalue	*find_in_dictionary(t_list *dict, char *key)
{
	t_list		*cursor;
	t_keyvalue	*kv;

	if (key == NULL)
		return (NULL);
	cursor = dict;
	while (cursor)
	{
		kv = (t_keyvalue *) cursor->content;
		if (ft_strcmp(key, kv->key) == 0)
			return (kv);
		cursor = cursor->next;
	}
	return (NULL);
}

void	remove_word_from_dictionary(t_list **dict, char *key)
{
	t_list		*cursor;
	t_list		*prev;
	t_keyvalue	*kv;

	if (dict == NULL || *dict == NULL || key == NULL)
		return ;
	cursor = *dict;
	prev = NULL;
	while (cursor)
	{
		kv = (t_keyvalue *) cursor->content;
		if (ft_strcmp(key, kv->key) == 0)
		{
			if (prev == NULL)
				*dict = cursor->next;
			else
				prev->next = cursor->next;
			ft_lstdelone(cursor, (t_lstdel)destroy_keyvalue);
			return ;
		}
		prev = cursor;
		cursor = cursor->next;
	}
}
