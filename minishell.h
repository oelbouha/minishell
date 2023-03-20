/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:19:24 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/10 19:22:31 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

# define PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"

/*								   structurs
	==========================================================================
*/

typedef struct s_shell
{
	char		**pipes;
	char		**cmds;
	char		*cmd_path;
	char		**simple_cmd;
	int			number_of_pipes;
	int			number_of_cmds;
	int			pipe1[2];
	int			pipe2[2];
	int			fdout;
	int			fdin;
	int			pid;
}				t_shell;

typedef struct s_redirections
{
	t_list	*infile;
	t_list	*outfile;
	t_list	*append;
	t_list	*here_doc_delimiter;
	t_list	*cmds;
	int		index;
}			t_redirections;

typedef struct s_tokens
{
	t_redirections redirections;
}	t_tokens;
/*								   functions
	==========================================================================
*/

void	execute_command(char **arr, char **env);
char	*make_path(char *cmd);
char	*path_from_env(char **env);
char	check_path(char *cmd);
void	read_input(char **env);
void	run_command(t_shell *shell, char **env);
void	ft_free(char **arr);

/*								 pipes functions
	==========================================================================
*/

void	setup_pipes_for_child(int i, int *pipe1, int *pipe2);
void	setup_pipes_for_last_child(int i, int *pipe1, int *pipe2);
void	setup_pipes_for_next_child(int i, int *pipe1, int *pipe2);
int		check_pipe_error(char **arr, char *line);
int		count_pipes(char **arr);
int		check_pipes(char *str);
void	create_pipes(int *pipe1, int *pipe2);

/*							redirections functions
	==========================================================================
*/

void	setup_infile(t_list *infile);
void	setup_outfile(t_list *outfile);
void	setup_append(t_list *append);
void	parse_redirections(char **arr, t_redirections *redirections);
int		check_redirection(char *str, char *next_arg);
int		valid_redirection(char **str);
int		setup_infile_redirection(char *str, t_redirections *red, char *word);
int		setup_heredoc(char *str, t_redirections *red, char *word);
void	setup_redirections(t_redirections *red, t_shell *shell, char **env);
char	**copy_from_list(t_list *cmd);

/*							error functions
	==========================================================================
*/
void	parse_error();
void	free_lst(t_list *lst);
void	print_error_msg(char *str, char *msg, int exit_status, char **arr);
void	free_tokens(t_redirections **red);

/****************** just for testing ***************/
void	print_list(t_list *lst);
void	print(char **arr);
#endif
