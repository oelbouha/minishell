/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.check_common_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:41:58 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/11 17:53:30 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_bonus.h"

void	check_pipe(t_list *prev, t_list *cur, t_analyzer_stats *stats)
{
	int	err;

	if (prev == NULL && cur == NULL)
		stats->syntax_error += 1;
	else if (prev && cur == NULL)
		stats->syntax_error += (ft_strcmp(prev->content, "|") == 0);
	else if (prev && ft_strcmp(cur->content, "|") == 0)
	{
		err = ft_templatecmp(prev->content, CANT_BE_BEFORE_PIPE, ':');
		stats->syntax_error += err;
	}
}

void	check_redirs(t_list *prev, t_list *cur, t_analyzer_stats *stats)
{
	if (prev == NULL && cur == NULL)
		stats->syntax_error += 1;
	else if (prev && cur == NULL)
		stats->syntax_error += ft_templatecmp(prev->content, REDIRS, ':');
	else if (prev && ft_templatecmp(cur->content, REDIRS, ':'))
	{
		stats->syntax_error += ft_templatecmp(prev->content, REDIRS, ':');
		stats->heredoc_count += (ft_strcmp(cur->content, "<<") == 0);
	}
}

char	check_for_unclosed_quote(char *token)
{
	char	quote;

	quote = 0;
	while (*token)
	{
		if (*token == '"' || *token == '\'')
		{
			quote = *token;
			token = ft_strchr(token + 1, quote);
			if (token == NULL)
				return (quote);
		}
		token++;
	}
	return (0);
}

void	check_word(t_list *prev, t_list *cur, t_analyzer_stats *stats)
{
	int		err;

	if (prev == NULL && cur == NULL)
		stats->syntax_error += 1;
	else if (prev && cur && !ft_templatecmp(cur->content, OPERATORS, ':'))
	{
		if (cur->next == NULL)
			stats->unclosed_quote = check_for_unclosed_quote(cur->content);
		if (stats->unclosed_quote)
			return ;
		err = stats->cant_be_word;
		err = (err && !ft_templatecmp(prev->content, REDIRS, ':'));
		err += ft_strcmp(prev->content, ")") == 0;
		stats->syntax_error += err;
	}
}
