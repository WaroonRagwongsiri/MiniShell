/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:06:05 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 13:35:24 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define PATH_MAX 1024

/*
TODO : handle echo with " "
*/
int	builtin_echo(t_cmd_group *cmd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (cmd->argv[1] != NULL && ft_strncmp(cmd->argv[1], "-n", 2) == 0)
	{
		newline = false;
		i = 2;
	}
	while (cmd->argv[i] != NULL)
	{
		ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		if (cmd->argv[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	close_builtin_fds(cmd);
	return (0);
}

int	builtin_pwd(t_cmd_group *cmd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		close_builtin_fds(cmd);
		return (0);
	}
	perror("pwd");
	close_builtin_fds(cmd);
	return (1);
}

static void	update_pwd(char ***env_ptr)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;

	new_pwd = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	if (new_pwd != NULL)
		set_env_var(env_ptr, new_pwd);
}

int	builtin_cd(t_cmd_group *cmd)
{
	char	*path;

	if (cmd->argv[1] == NULL)
	{
		path = ft_getenv(*(cmd->env_ptr), "HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			close_builtin_fds(cmd);
			return (1);
		}
	}
	else
		path = cmd->argv[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		close_builtin_fds(cmd);
		return (1);
	}
	update_pwd(cmd->env_ptr);
	close_builtin_fds(cmd);
	return (0);
}

int	builtin_exit(t_cmd_group *cmd)
{
	int	exit_code;

	exit_code = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->argv[1] != NULL)
		exit_code = ft_atoi(cmd->argv[1]);
	close_builtin_fds(cmd);
	exit(exit_code);
}
