

#include "executer.h"


int	command_not_found(char *cmd_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit (127);
}

char	*get_cmd_path(char *cmd_name)
{
	char	**path;
	char	*cmd_path;
	char	*str;
	int		i;

	path = get_path();
	if (ft_strchr(cmd_name, '/'))
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
