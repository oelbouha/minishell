/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:02:41 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 11:33:57 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "minishell.h"
# include "minishell_types.h"

int	execute_simple_command(t_cmd *cmd, t_bool force_fork, t_bool wait_child);
int	execute_compound_command(t_cmd *cmd);
int	execute_subshell_command(t_cmd *cmd, t_bool wait_child);
int	prep_redirs(t_list *redirs);

int	get_exit_status(pid_t pid);

#endif
