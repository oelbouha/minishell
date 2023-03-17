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

/*								   functions
	==========================================================================
*/

void	print(char **arr);
void	execute_command(char **arr, char *path, char **env);
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

/*							redirections functions
	==========================================================================
*/

int		setup_trunc_and_append_file(char *str, t_redirections *red, char *word);
int		setup_infile_and_heredoc(char *str, t_redirections *red, char *word);
void	setup_redirections(char **arr, t_redirections *redirections);
int		check_here_doc(char *str);
int		check_redirection(char *str);
int		valid_redirection(char **str);
int		setup_infile_redirection(char *str, t_redirections *red, char *word);
int		setup_heredoc(char *str, t_redirections *red, char *word);
int		setup_trunc_and_append_file(char *str, t_redirections *red, char *word);
int		setup_append_file(char *str, t_redirections *red, char *word);
int		setup_trunc_file(char *str, t_redirections *red, char *word);

/*							error functions
	==========================================================================
*/
void	parse_error();
void	print_error_msg(char *str, char *msg, int exit_status, char **arr);

#endif
