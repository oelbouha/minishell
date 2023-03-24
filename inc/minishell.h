/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:25:44 by ysalmi            #+#    #+#             */
/*   Updated: 2023/03/24 17:06:39 by ysalmi           ###   ########.fr       */
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
typedef void 				(*t_lstdel)(void *);


struct s_shell
{
	t_list	*env;
	t_list	*exports;
	t_list	*builtins;
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

t_keyvalue	*new_keyvalue(char *key, char *value);
void		destroy_keyvalue(t_keyvalue *kv);

#endif
