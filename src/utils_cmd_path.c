/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:16:28 by waragwon          #+#    #+#             */
/*   Updated: 2025/11/03 13:54:45 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmdpath(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int	is_directory(char *cmdpath)
{
	struct stat	statbuff;

	if (lstat(cmdpath, &statbuff) == 0)
	{
		if (S_ISDIR(statbuff.st_mode))
			return (1);
	}
	return (0);
}

static char	*check_cmd_path(char *cmdpath)
{
	if (is_directory(cmdpath))
		exit_cmd(cmdpath, ": Is a directory", 126);
	if (access(cmdpath, F_OK) == -1)
		exit_cmd(cmdpath, ": No such file or directory", 127);
	if (access(cmdpath, F_OK | X_OK) == -1)
		exit_cmd(cmdpath, ": Permission denied", 126);
	return (cmdpath);
}

static char	*ft_build_path(char *path, char *cmd)
{
	char	*temp_path;
	char	*cmd_path;

	temp_path = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(temp_path, cmd);
	return (cmd_path);
}

char	*find_cmd(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*env_var;

	if (is_cmdpath(cmd))
		return (check_cmd_path(cmd));
	i = 0;
	env_var = ft_getenv(env, "PATH");
	if (env_var == NULL)
		return (NULL);
	paths = ft_split(env_var, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_path = ft_build_path(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}
