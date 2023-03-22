/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:55:47 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/21 19:55:49 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **env, t_shell *shell)
{
	int		i;
	t_list	*temp;

	i = -1;
	while (env[++i])
		ft_lstadd_back(&shell->env, ft_lstnew(env[i]));
	temp = shell->env;
	while (temp)
	{
		ft_putstr_fd(temp->content, 1);
		write (1, "\n", 1);
		temp = temp->next;
	}
	free_lst(shell->env);
}