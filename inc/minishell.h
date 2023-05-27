/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:25:44 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/26 19:36:23 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include "libft.h"
# include "core.h"
# include "minishell_types.h"

t_list	*tokenize(const char *line);
int		analyze(t_list **tokens);

t_list	*new_command(t_list **head, t_cmd_exec_cond cond);
void	destroy_command(t_cmd *cmd);

int		execute(t_list *cmd);

int		is_an_operator(const char *token);

#endif
