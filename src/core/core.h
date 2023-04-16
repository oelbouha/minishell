/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:10:22 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/16 17:51:49 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "libft.h"
typedef int					t_builtin(int c, char *v[]);

int			setup(char *env[]);
int			set_env_var(char *key, char *value);
char		*get_env_var(char *key);
t_builtin	*get_builtin(char *key);
char		*get_current_wd(void);
int			get_last_status(void);
int			set_last_status(unsigned char status);
void		msh_err(char *msg, char *token);

#endif
