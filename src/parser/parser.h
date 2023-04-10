/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:22:03 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/10 14:17:17 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H






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

typedef enum e_type_redir
{
	HEREDOC,
	FILEREDIR
}	t_type_redir;

typedef union u_cmd				t_cmd_u;
typedef struct s_cmd			t_cmd;
typedef struct s_simple_cmd		t_simple_cmd;
typedef struct s_compound_cmd	t_compound_cmd;
typedef union u_redir			t_redir_u;
typedef struct s_redir			t_redir;
typedef struct s_file_redir		t_file_redir;

union u_cmd
{
	t_simple_cmd	*s_cmd;
	t_compound_cmd	*c_cmd;
};

struct s_cmd
{
	t_cmd_u			*cmd;
	t_cmd_type		cmd_type;
	int				count;
	t_cmd_exec_cond	cond;
	t_list			redirs;
};

struct s_simple_cmd
{
	char	*cmd_path;
	char	**cmd_args;
};

struct s_compound_cmd
{
	t_list	*cmds[];
	int		parentheses;
};

union u_redir
{
	t_file_redir	*redir;
	int				fd;
};

struct s_redir
{
	t_redir_u		*redir;
	t_type_redir	type;
};

struct s_file_redir
{
	char	*file;
	int		to;
	int		append;
};

#endif
