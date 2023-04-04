/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:10:22 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/04 17:49:41 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_INTERNAL_H
# define CORE_INTERNAL_H

# include "libft.h"
# include "datastructures.h"
# include "core.h"
# include <stdio.h>

/* ***  Definitions  **** */

typedef int					t_builtin(int c, char *v[]);
typedef struct s_shell		t_shell;
typedef unsigned char		t_uchar;

struct s_shell
{
	t_list	*env;
	t_list	*builtins;
	char	*wd;
	char	**path;
	t_uchar	last_stts;
};


/* ***  Global variable  **** */

t_shell	g_shell;

t_list	*construct_builtins_list(void);

/* ***  Builtins  **** */
int	cd(int c, char **v);
int	echo(int c, char **v);
int	shell_export(int c, char **v);
int	pwd(int c, char **v);
int	env(int c, char **v);
int	unset(int c, char **v);
#endif