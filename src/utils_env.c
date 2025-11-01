/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:58:30 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/01 19:26:53 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_getenv(char **env, char *key)
{
	int	i;
	int	len_key;

	if (env == NULL || key == NULL)
		return (NULL);
	i = 0;
	len_key = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, len_key) == 0)
		{
			if (env[i][len_key] == '=')
				return (&env[i][len_key + 1]);
		}
		i++;
	}
	return (NULL);
}

static char	*ft_build_path(char *path, char *cmd)
{
	char	*temp_path;
	char	*cmd_path;

	temp_path = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(temp_path, cmd);
	return (cmd_path);
}

char	*ft_get_cmd_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*env_var;

	i = 0;
	env_var = ft_getenv(env, "PATH");
	if (env_var == NULL)
		return (NULL);
	paths = ft_split(env_var, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_path = ft_build_path(paths[i], cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free_tab(paths);
			return (cmd_path);
		}
		i++;
	}
	free_tab(paths);
	return (NULL);
}
