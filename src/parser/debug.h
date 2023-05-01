/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:57:37 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/30 15:57:38 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "minishell_types.h"

void	print_cmd(t_cmd *cmd, int n);
void	print_simple_cmd(t_cmd *cmd, int n);
void	print_compound_cmd(t_cmd *cmd, int n);

#endif
