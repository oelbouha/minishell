/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:02:41 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/13 19:49:07 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "minishell.h"
# include "minishell_types.h"

int		execute_simple_command(t_cmd *cmd, t_bool force_fork, t_bool wait_child);

int		get_exit_status(pid_t pid);

#endif
