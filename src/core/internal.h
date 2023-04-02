/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:10:22 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/02 12:32:53 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_INTERNAL_H
# define CORE_INTERNAL_H

# include "minishell.h"

/* ***  Definitions  **** */

typedef struct s_shell		t_shell;
struct s_shell
{
	t_list	*env;
	t_list	*builtins;
	char	*separators;
	char	*wd;
	t_uchar	last_stts;
};


/* ***  Global variable  **** */

t_shell	shell;




#endif
