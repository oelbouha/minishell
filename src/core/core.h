/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:10:22 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/26 15:52:34 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "libft.h"

typedef int					(*t_builtin)(int c, char *v[]);

int			setup(char *env[]);
void		destroy(void);
int			set_state(int value);
int			get_state(void);
int			set_env_var(char *key, char *value);
char		*get_env_var(char *key);
int			get_env_var_len(char *key);
char		**get_env_arr(void);
t_builtin	get_builtin(char *key);
char		*get_current_wd(void);
int			get_last_status(void);
int			set_last_status(int status);
char		**get_path(void);
void		msh_log(char *cmd, char *msg, char *arg, t_bool quotes);
void		msh_err(char *msg, char *token);

#endif
