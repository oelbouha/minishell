/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:10:22 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/14 15:34:05 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_INTERNAL_H
# define CORE_INTERNAL_H

# include <sys/errno.h>
# include <string.h>
# include "libft.h"
# include "datastructures.h"
# include "core.h"
# include <stdio.h>

/* ***  Definitions  **** */

typedef struct s_shell		t_shell;
typedef unsigned char		t_uchar;

struct s_shell
{
	t_list	*env;
	t_list	*builtins;
	char	*wd;
	char	**paths;
	int		last_stts;
};

/* ***  Global variable  **** */

t_shell						g_shell;

t_list	*construct_builtins_list(void);

/* ***  Builtins  **** */
int		cd(int c, char **v);
int		echo(int c, char **v);
int		shell_export(int c, char **v);
int		pwd(int c, char **v);
int		env(int c, char **v);
int		unset(int c, char **v);
int		shell_exit(int c, char **v);

/* ***  Utils  **** */
int		check_identifier(char *id);
void	msh_log(char *cmd, char *msg, char *arg, t_bool quotes);
#endif
