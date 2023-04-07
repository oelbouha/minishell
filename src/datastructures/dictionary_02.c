/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:05:54 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/07 11:29:56 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"

void	update_keyvalue(t_keyvalue *kv, char *key, void *value)
{
	if (kv)
	{
		free(kv->key);
		kv->key = key;
		kv->value = value;
	}
}

int	add_word_to_dictionary(t_list **dict, char *key, void *value)
{
	t_keyvalue	*kv;
	t_list		*entry;

	kv = new_keyvalue(key, value);
	if (kv == NULL)
		return (1);
	entry = ft_lstnew(kv);
	if (entry == NULL)
		return (destroy_keyvalue(kv), 1);
	ft_lstadd_back(dict, entry);
	return (0);
}
