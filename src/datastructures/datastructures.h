/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datastructures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:04:26 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/07 11:28:02 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCTURES_H
# define DATASTRUCTURES_H

# include "libft.h"

typedef struct s_keyvalue	t_keyvalue;

struct s_keyvalue
{
	char	*key;
	void	*value;
};

t_keyvalue	*new_keyvalue(char *key, void *value);
void		update_keyvalue(t_keyvalue *kv, char *key, void *value);
void		destroy_keyvalue(t_keyvalue *kv);
t_list		*new_dictionary(char **arr, char sep);
t_keyvalue	*find_in_dictionary(t_list *dict, char *key);
int			add_word_to_dictionary(t_list **dict, char *key, void *value);
void		remove_word_from_dictionary(t_list **dict, char *key);

#endif
