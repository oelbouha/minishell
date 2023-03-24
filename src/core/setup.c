/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:59:29 by ysalmi            #+#    #+#             */
/*   Updated: 2023/03/24 23:22:55 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "core.h"
//
//
//
//
//
//	fill env dictionary
//	fill builtins dictionary
//	fill separators 
//	fill working dir
//	
//

int	setup(char **env)
{
	shell.env = new_dictionary(env, '=');
	if (shell.env == NULL)
		return (1);
	shell.builtins = get_builtins();
	if (shell.builtins == NULL)
		return (destroy_dictionary(shell.env), 1);
	shell.separators = "\t\r ";
	shell.wd = get_working_directory();
	if (shell.wd == NULL)
		return ()
}
