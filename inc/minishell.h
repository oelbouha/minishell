/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:25:44 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/20 12:28:50 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <sys/errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include "libft.h"
# include "core.h"
# include "debug.h"

# define NO_REDIRS (t_list *)-1
# define EMPTY_LST	(t_list *)-1

typedef unsigned long long		t_ull;

char	*read_line(t_ull state);
t_list	*tokenize(const char *line);
int		analyze(t_list **tokens);
void	print(t_list *lst);

t_list	*new_command(t_list **head, t_cmd_exec_cond cond);
void	destroy_command(t_cmd *cmd);

int		execute(t_list *cmd);

int		is_an_operator(const char *token);

#endif
