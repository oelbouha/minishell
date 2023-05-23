/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:02:41 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/23 20:37:00 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_BONUS_H
# define EXECUTER_BONUS_H

# include "executer.h"

int		execute_subshell_command(t_cmd *cmd, t_bool wait_child);

t_list	*wildcard(char *line);
t_list	*expand_wildcard(t_list *lst);

#endif
