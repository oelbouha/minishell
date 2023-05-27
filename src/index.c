/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:30:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/26 19:34:40 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(void)
{
	char	*trimmed;
	char	*line;

	line = NULL;
	while (ft_issubset(" \t", line))
	{
		free(line);
		set_state(0);
		line = readline("→ ");
		if (line == NULL)
			return (line);
	}
	add_history(line);
	trimmed = ft_strtrim(line, " \t");
	return (free(line), trimmed);
}

int	main(int c, char **v, char **e)
{
	char	*line;
	t_list	*tokens;
	t_list	*command;
	int		err;

	v = v + c;
	if (setup(e))
		return (destroy(), 1);
	while (1)
	{
		line = get_line();
		if (line == NULL)
			return (destroy(), get_last_status());
		tokens = tokenize(line);
		err = analyze(&tokens);
		command = new_command(&tokens, NONE);
		if (err && get_state() == 0)
			set_last_status(258);
		else if (get_state() == 0 && set_state(1))
			execute(command);
		free(line);
		ft_lstclear(&command, (t_lstdel)destroy_command);
		if (get_state() == 3 || get_last_status() < 0)
			return (destroy(), get_last_status());
	}
}
