/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:24:22 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/27 14:38:07 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char	**prep_args(t_list *args_lst)
{
	char	**arr;
	t_list	*args;

	args = expand(args_lst);
	if (args == NULL)
		return (NULL);
	else if (args == (t_list *)-1)
		args = NULL;
	arr = ft_lst_to_arr(args);
	if (arr == NULL)
		return (ft_lstclear(&args, free), NULL);
	ft_lstclear(&args, do_nothing);
	return (arr);
}
