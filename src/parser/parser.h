/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:22:03 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/08 23:29:02 by ysalmi           ###   ########.fr       */
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
	PIPE,
	AND,
	OR
}	t_cmd_exec_cond;

typedef union u_cmd			t_cmd_u;
typedef struct s_cmd		t_cmd;
typedef struct simple_cmd	t_simple_cmd;
typedef struct compound_cmd	t_compound_cmd;

union u_cmd
{
	t_simple_cmd	*s_cmd;
	t_compound_cmd	*c_cmd;
};




#endif
