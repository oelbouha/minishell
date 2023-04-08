/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:13:39 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/08 12:10:45 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	my_redisplay(void)
{
	ft_printf("                         ");
}
int	startup_hook(const char *str, int n)
{
//	ft_printf("startup hook [%s] [%d]\n", str, n);
	(void)str;
	(void)n;
	return (0);
}
void	configure_readline(void)
{
	rl_redisplay_function = my_redisplay;
	rl_startup_hook = startup_hook;
	return ;
}

void	*get_prompt(void)
{
	char	*prompt;
	char	*user;
	char	*wd;
	int		len;;
	int		i;

	user = get_env_var("USER");
	wd = get_current_wd();
	len = 0;
	if (user)
		len = ft_strlen(user) + 13;
	if (wd)
		len += ft_strlen(ft_strrchr(wd, '/') + 1) + 14 + 16;
	printf("len: %d\n", len);
	prompt = ft_calloc(1, len + 1);
	i = ft_strlen("\x1b[34;01m[ ");
	ft_memcpy(prompt, "\x1b[34;01m[ ", i);
	len = ft_strlen(user);
	ft_memcpy(&prompt[i], user, len);
	i += len;
	len = ft_strlen(" ] \x1b[36;01m@[ ");
	ft_memcpy(&prompt[i], " ] \x1b[36;01m@[ ", len);
	i += len;
	len = ft_strlen(ft_strrchr(wd, '/') + 1);
	ft_memcpy(&prompt[i], ft_strrchr(wd, '/') + 1, len);
	i += len;
	len = ft_strlen(" ] \x1b[31;01m-〉\x1b[0m");
	if (get_last_status())
		ft_memcpy(&prompt[i], " ] \x1b[31;01m-〉\x1b[0m", len);
	else
		ft_memcpy(&prompt[i], " ] \x1b[32;01m-〉\x1b[0m", len);
	printf("i: %d\n", i + len);
	len = ft_strlen(user) + ft_strlen(ft_strrchr(wd, '/') + 1) + 14;
	rl_display_prompt = ft_calloc(1, len + 1);
	for (i = 0; i < len; i++)
		rl_display_prompt[i] = '_';
	return (prompt);
	/*


	if (v)
		ft_printf("\x1b[34;01m[ %s ] ", v);
	free(v);
	v = get_current_wd();
	if (v)
	{
		ft_printf("\x1b[36;01m@[ %s ] ", &v[i + 1]);
	}
	free(v);
	if (get_last_status())
		ft_printf("\x1b[31;01m");
	else
		ft_printf("\x1b[32;01m");
		*/
}
//[ ysalmi ] @[ lexer ] -〉fdkjfd                      
/*
 *		Description
 *
 *	@params:
 *		@state: indicate if it's the first call to the function (state = 0)
 *	
 *	@return:
 *		returns the line read
 */

char	*get_line(t_ull state)
{
	char	*line;
	char	*prompt;

	if (state == 0)
		configure_readline();
	prompt = get_prompt();
	line = readline(prompt);
	free(prompt);
	return (line);
}

int	main(int c, char **v, char **e)
{
	(void)c;
	(void)v;
	//temperary
	setup(e);
	char *line = get_line(0);
	printf("%s\n", line);
	return (0);
}
