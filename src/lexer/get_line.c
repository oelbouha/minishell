/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:13:39 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/11 19:42:40 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	configure_readline(void)
{
	return ;
}

char	*get_styled_user(int wd)
{
	static char		*styled_user;
	static size_t	len;
	char			*user;

	if (styled_user == NULL)
	{
		user = get_env_var("USER");
		if (user == NULL)
			return (NULL);
		len = ft_strlen(user) + ft_strlen("\x1b[34;01m[  ] \x1b[36;01m@[ ");
		styled_user = malloc(256);
		if (styled_user == NULL)
			return (free(user), NULL);
		ft_strlcat(styled_user, "\x1b[34;01m[ ", 256);
		ft_strlcat(styled_user, user, 256);
		ft_strlcat(styled_user, " ]", 256);
		free(user);
	}
	if (wd && len > ft_strlen(styled_user))
		ft_strlcat(styled_user, " \x1b[36;01m@[ ", 256);
	else if (wd == 0 && len == ft_strlen(styled_user))
		styled_user[ ft_strrchr(styled_user, ']') - styled_user + 1 ] = 0;
	return (styled_user);
}

void	*get_prompt(void)
{
	char	*prompt;
	char	*wd;

	wd = get_current_wd();
	if (ft_strlen(ft_strrchr(wd, '/')) > 70)
	{
		free(wd);
		wd = NULL;
	}
	prompt = get_styled_user(wd != NULL);
	if (prompt == NULL)
		return (free(wd), NULL);
	if (wd && ft_strchr(prompt, '@'))
	{
		prompt[ft_strchr(prompt, '@') - prompt + 3] = 0;
		ft_strlcat(prompt, ft_strrchr(wd, '/') + 1, 256);
		ft_strlcat(prompt, " ]", 256);
	}
	else
		prompt[ft_strchr(prompt, ']') - prompt + 1] = 0;
	if (get_last_status())
		ft_strlcat(prompt, " ▌\x1b[31;01m→ \x1b[0m", 256);
	else
		ft_strlcat(prompt, " ▌\x1b[32;01m→ \x1b[0m", 256);
	return (free(wd), prompt);
}

char	*read_line(t_ull state)
{
	char	*line;
	char	*prompt;

	if (state == 0)
		configure_readline();
	prompt = get_prompt();
	line = NULL;
	while (line == NULL || *line == 0)
	{
		if (prompt)
			line = readline(prompt);
		else
			line = readline("→ ");
	}
	add_history(line);
	return (line);
}

int	main(int c, char **v, char **e)
{
	(void)c;
	(void)v;
	setup(e);
	while (1)
	{
		char *line = read_line(0);
		ft_printf("line: [%s]\n", line);
		set_last_status(get_last_status()?0:1);
		free(line);
	}
	return (0);
}
