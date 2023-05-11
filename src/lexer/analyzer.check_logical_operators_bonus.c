/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.check_logical_operators_bonus.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:41:58 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/11 11:30:03 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_bonus.h"

void	check_logical_ops(t_list *prev, t_list *cur, t_analyzer_stats *stats)
{
	int	err;

	if (prev == NULL && cur == NULL)
		stats->syntax_error += 1;
	else if (prev && cur == NULL)
	{
		err = ft_templatecmp(prev->content, "&&:||", ':');
		stats->syntax_error += err;
	}
	else if (prev && ft_templatecmp(cur->content, "&&:||", ':'))
	{
		err = ft_templatecmp(prev->content, "|:>>:<<:>:<:&&:||:(", ':');
		stats->syntax_error += err;
	}
}
