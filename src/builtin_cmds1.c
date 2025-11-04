/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:06:05 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 17:15:00 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define PATH_MAX 1024

int	builtin_echo(t_cmd_group *cmd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (cmd->argv[1] != NULL && ft_strncmp(cmd->argv[1], "-n", 2) == 0)
	{
		if (is_valid_echo_flag(cmd->argv[1] + 2))
		{
			newline = false;
			i = 2;
		}
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

static int	update_pwd(char ***env_ptr, int update_old_pwd)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;

	if (update_old_pwd)
		new_pwd = ft_strjoin("OLDPWD=", getcwd(cwd, sizeof(cwd)));
	else
		new_pwd = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	if (new_pwd != NULL)
		set_env_var(env_ptr, new_pwd);
	return (1);
}

int	builtin_cd(t_cmd_group *cmd)
{
	char	*path;

	if (tab_len(cmd->argv) > 2)
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO), 1);
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
	if (update_pwd(cmd->env_ptr, 1) && chdir(path) != 0)
	{
		perror("cd");
		close_builtin_fds(cmd);
		return (1);
	}
	update_pwd(cmd->env_ptr, 0);
	close_builtin_fds(cmd);
	return (0);
}

int	builtin_exit(t_cmd_group *cmd)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	if (cmd->argv[0] == NULL || cmd->argv[1] == NULL)
		exit(0);
	if (cmd->argv[1] != NULL)
		exit_code = ft_atoi(cmd->argv[1]);
	i = -1;
	while (cmd->argv[1][++i] != '\0' && tab_len(cmd->argv) == 2)
	{
		if (ft_isalpha(cmd->argv[1][i]))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			return (close_builtin_fds(cmd), 2);
		}
	}
	if (tab_len(cmd->argv) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (close_builtin_fds(cmd), 1);
	}
	close_builtin_fds(cmd);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_code);
}
