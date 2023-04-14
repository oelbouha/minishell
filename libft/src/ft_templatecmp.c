/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_templatecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:16:17 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/14 15:29:29 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_templatecmp(char *str, char *template, char delimiter)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (template[i])
	{
		if (ft_strncmp(str, &template[i], len) == 0)
			if (template[i + len] == delimiter || template[i + len] == 0)
				return (1);
		while (1)
		{
			if (template[i] == delimiter)
				break ;
			else if (template[i] == 0)
				return (0);
			i++;
		}
		i++;
	}
	return (0);
}
/*
void	ft_free(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

=======
>>>>>>> 4379e4eb3902b6a84e233f6475be00e83033f707
int	ft_templatecmp(char *str, char *template, char delimiter)
{
	int		i;
	char	**arr;

	i = -1;
	while (arr[++i])
	{
<<<<<<< HEAD
		if (ft_strncmp(str, &template[i], len) == 0)
			if (template[i + len] == delimiter || template[i + len] == 0)
				return (1);
		while (template[i] && template[i] != delimiter)
			i++;
		if (template[i] == 0)
			return (0);
		i++;
=======
		if (ft_strcmp(str, arr[i]) == 0)
<<<<<<< HEAD
		{
			ft_free(arr);
			return (1);
		}
>>>>>>> 594fb2c15507109cca103ab856ef9ed04c53d90a
	}
	ft_free(arr);
	return (0);
}*/
