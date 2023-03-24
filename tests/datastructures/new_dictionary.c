/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dictionary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:11:47 by ysalmi            #+#    #+#             */
/*   Updated: 2023/03/24 17:49:56 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"
#include "test.h"

int	new_dict(void)
{
	char	*arr[] = {"key:value", "cle:valeur", NULL};
	t_list	*dict = new_dictionary(arr, ':');
	printf("dictionary:\n{\n");
	while (dict)
	{
		t_keyvalue	*kv = (t_keyvalue *) dict->content;
		printf("\t%s:\t%s\n", kv->key, kv->value);
		dict = dict->next;
	}
	printf("}\n");
	return (0);
}
