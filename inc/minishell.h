/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:25:44 by ysalmi            #+#    #+#             */
/*   Updated: 2023/03/24 23:09:13 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

/* ************************************************************************** */
/* ***  Structs, Enums and Types  ******************************************* */
/* ************************************************************************** */
typedef unsigned char		t_uchar;
typedef struct s_shell		t_shell;
typedef struct s_cmd		t_cmd;
typedef struct s_redir		t_redir;


struct s_shell
{
	t_list	*env;
	t_list	*builtins;
	char	*separators;
	char	*wd;
	t_uchar	last_cmd_stts;
};

struct s_cmd
{
	char	*exec;
	char	**args;
	t_list	*redirs;
};

struct s_redir
{
	int		fd;
	char	**to;
};

#endif
