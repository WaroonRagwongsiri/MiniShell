/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:57:20 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 11:03:26 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_build_path(char *path, char *cmd)
{
	char	*temp_path;
	char	*cmd_path;

	temp_path = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	return (cmd_path);
}

static char	*ft_get_cmd_path(char *cmd, char **env)
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
		free(cmd_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

int	ft_execve(char *cmd_path, char **cmd, char **env)
{
	int	status;
	int	i;

	if (process_redirect(cmd))
	{
		i = 0;
		while (!is_redirect_char(cmd[i][0]))
			i++;
		while (cmd[i] != NULL)
		{
			cmd[i] = NULL;
			i++;
		}
	}
	status = execve(cmd_path, cmd, env);
	return (status);
}

int	execute_command(char **cmd, char **env)
{
	pid_t	pid;
	char	*cmd_path;

	if (cmd[0] == NULL)
		return (0);
	if (is_builtin(cmd[0]))
		return (execute_builtin(cmd, env));
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		cmd_path = ft_get_cmd_path(cmd[0], env);
		if (cmd_path == NULL || ft_execve(cmd_path, cmd, env) == -1)
		{
			perror(cmd[0]);
			return (127);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
