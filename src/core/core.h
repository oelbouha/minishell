/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:10:22 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/11 15:19:27 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "libft.h"

int			setup(char *env[]);
t_list		get_env_list(void);
int			set_env_var(char *key, char *value);
char		*get_env_var(char *key);
t_list		get_builtins_list(void);
char		*get_current_wd(void);
int			get_last_status(void);
int			set_last_status(unsigned char status);
void		msh_err(char *msg, char *token);

#endif
