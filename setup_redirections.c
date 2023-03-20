/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:19:02 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/18 15:19:03 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_infile(t_list *infile)
{
	int		fd;
	t_list	*lst;

	lst = infile;
	if (ft_lstsize(lst))
	{
		while (lst)
		{
			fd = open(lst->content, O_RDONLY);
			if (access(lst->content, F_OK) < 0)
				print_error_msg(lst->content, ": No such file or directory", 0, 0);
			if (access(lst->content, R_OK) < 0)
				print_error_msg(lst->content, ": permission denied", 1, 0);
			dup2(fd, 0);
			close(fd);
			lst = lst->next;
		}
	}
}

void	setup_outfile(t_list *outfile)
{
	int		fd;
	t_list	*lst;

	lst = outfile;
	if (ft_lstsize(lst))
	{
		while (lst)
		{
			fd = open(lst->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd == - 1)
			{
				perror("minishell");
				exit(1);
			}
			dup2(fd, 1);
			close(fd);
			lst = lst->next;
		}
	}
}

void	setup_append(t_list *append)
{
	int		fd;
	t_list	*lst;

	lst = append;
	while (lst)
	{
		
		fd = open(lst->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == - 1)
		{
			perror("minishell: outfile");
			exit(1);
		}
		dup2(fd, 1);
		close(fd);
		lst = lst->next;
	}
}

// void	setup_here_doc(t_list *here_doc)
// {
// 	int		fd;

// 	while (here_doc)
// 	{
// 		fd = open(append, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == - 1)
// 		{
// 			perror("minishell");
// 			exit(1);
// 		}
// 		dup2(fd, 1);
// 	}
// }