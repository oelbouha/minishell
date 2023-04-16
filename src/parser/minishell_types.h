/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:22:03 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/16 14:39:57 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPES_H
# define MINISHELL_TYPES_H

# include "libft.h"

typedef enum e_cmd_type
{
	SIMPLE_CMD,
	COMPOUND_CMD
}	t_cmd_type;

typedef enum e_cmd_exec_cond
{
	NONE,
	AND,
	OR
}	t_cmd_exec_cond;

typedef enum e_redir_type
{
	HEREDOC,
	FILE_IN,
	FILE_OUT,
	FILE_APPEND
}	t_redir_type;

typedef union u_cmd				t_cmd_u;
typedef struct s_cmd			t_cmd;
typedef struct s_simple_cmd		t_simple_cmd;
typedef struct s_compound_cmd	t_compound_cmd;
typedef union u_redir			t_redir_u;
typedef struct s_redir			t_redir;
typedef struct s_heredoc		t_heredoc;
typedef char *					t_file_redir;

struct s_simple_cmd
{
	char	*path;
	char	**args;
};

struct s_compound_cmd
{
	t_list	*cmds;
	t_bool	subshell;
};

union u_cmd
{
	t_simple_cmd	simple;
	t_compound_cmd	compound;
};

struct s_cmd
{
	t_cmd_u			data;
	t_cmd_type		type;
	int				count;
	t_cmd_exec_cond	cond;
	t_list			*redirs;
};

struct s_heredoc
{
	int		fd;
	t_bool	expand;
};

union u_redir
{
	t_file_redir	filename;
	t_heredoc		heredoc;
};

struct s_redir
{
	t_redir_u		to;
	t_redir_type	type;
};

#endif
