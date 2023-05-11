/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.check_parentheses_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:41:58 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/11 11:30:26 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_bonus.h"

void	check_parentheses(t_list *prev, t_list *cur, t_analyzer_stats *stats)
{
	int	err;

	if (prev == NULL && cur == NULL)
		stats->syntax_error += 1;
	else if (prev && cur == NULL)
	{
		err = (ft_strcmp(prev->content, "(") == 0);
		stats->parentheses_count += ft_strcmp(prev->content, "(") == 0;
	}
	else if (prev && ft_templatecmp(cur->content, "(:)", ':'))
	{
		if (ft_strcmp(cur->content, "(") == 0)
		{
			err = ft_templatecmp(prev->content, "|:&&:||:(", ':') == 0;
			stats->parentheses_count++;
		}
		else
		{
			err = ft_templatecmp(prev->content, "|:>:>>:<<:<:&&:||:(", ':');
			stats->parentheses_count--;
			stats->cant_be_word = 1;
		}
		stats->syntax_error += err;
	}
}
