

#include "executer.h"

int	check_cmd_path(char *cmd)
{
	DIR		*dir;

	if (*cmd == '/')
	{
		dir = opendir(cmd);
		if (dir)
		{
			closedir (dir);
			print_error_msg(cmd, ": is a directory", 126);
		}
	}
	if (*cmd == '.' || ft_strchr(cmd, '/'))
	{
		if (access(cmd,  F_OK) < 0)
			print_error_msg(cmd, ": No such file or directory", 127);
		else if (access(cmd,  X_OK) < 0)
			print_error_msg(cmd, ": permission denied", 126);
	}
	return (1);
}

char	*get_cmd_path(char *cmd_name)
{
	char	**path;
	char	*cmd_path;
	char	*str;
	int		i;

	path = g_shell.paths;
	if (ft_strchr(cmd_name, '/') && check_cmd_path(cmd_name))
		return (cmd_name);
	i = -1;
	while (path[++i] && *cmd_name)
	{
		str = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(str, cmd_name);
		free(str);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}
