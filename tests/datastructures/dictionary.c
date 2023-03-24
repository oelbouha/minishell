/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:35:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/03/24 22:05:02 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"
#include "test.h"

void	new_dict_test();
void	find_in_dict_test(char *key);
void	print_dict(t_list *dict);
void	remove_word_test(char *key);

int	main(void)
{
	new_dict_test();
	find_in_dict_test("fizz");
	remove_word_test("fizz");
	return (0);
}

void	new_dict_test(void)
{
	printf("\nNew dictionary from string[]\n===========================\n");
	char	*arr[] = {"key:value", 
						"cle:valeur",
						"foo:bar",
						"fizz:bazz",
						NULL};
	t_list	*dict = new_dictionary(arr, ':');
	print_dict(dict);
}

void	find_in_dict_test(char *key)
{
	printf("\nFinding word in dictionary\n===========================\n");
	char	*arr[] = {"key:value", 
						"cle:valeur",
						"foo:bar",
						"fizz:bazz",
						NULL};
	t_list	*dict = new_dictionary(arr, ':');
	t_keyvalue	*kv = find_in_dictionary(dict, key);
	if (kv)
		printf("found: %s => %s\n", kv->key, kv->value);
	else
		printf("not found\n");
}

void	remove_word_test(char *key)
{
	printf("\nRemove word from dictionary\n===========================\n");
	char	*arr[] = {"key:value", 
						"cle:valeur",
						"foo:bar",
						"fizz:bazz",
						NULL};
	t_list	*dict = new_dictionary(arr, ':');
	remove_word_from_dictionary(&dict, key);
	print_dict(dict);
}

void	print_dict(t_list *dict)
{
	printf("dictionary:\n{\n");
	while (dict)
	{
		t_keyvalue	*kv = (t_keyvalue *) dict->content;
		printf("\t%s:\t%s\n", kv->key, kv->value);
		dict = dict->next;
	}
	printf("}\n");
}
