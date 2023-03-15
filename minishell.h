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

typedef struct s_shell
{
	char	**pipes;
	char	**cmds;
	char	**simple_cmd;
	int		number_of_pipes;
	int		number_of_cmds;
	int		pipe1[2];
	int		pipe2[2];
}	t_shell;

void	print(char **arr);
void	print_error_msg(char *str, char *msg, int exit_status, char **arr);
void	execute_command(char **arr, char *path, char **env);
char	*make_path(char *cmd);
char	*path_from_env(char **env);
char	check_path(char *cmd);
void	read_input(char **env);
void	run_command(t_shell *shell, char **env);
void	ft_free(char **arr);

#endif
