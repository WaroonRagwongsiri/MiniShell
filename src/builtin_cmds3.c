/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:06:05 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/06 20:47:40 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define PATH_MAX 1024

int	builtin_echo_main(t_cmd_group *cmd)
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
		ft_putstr_fd(cmd->argv[i], cmd->out_fd);
		if (cmd->argv[i + 1] != NULL)
			ft_putstr_fd(" ", cmd->out_fd);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", cmd->out_fd);
	close_builtin_fds(cmd);
	return (0);
}

int	builtin_pwd_main(t_cmd_group *cmd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, cmd->out_fd);
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

int	builtin_cd_main(t_cmd_group *cmd)
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

int	builtin_exit_main(t_cmd_group *cmd)
{
	long	exit_code_long;
	int		exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->argv[1] == NULL)
		exit(g_status);
	if (!is_valid_numeric(cmd->argv[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		close_builtin_fds(cmd);
		exit(2);
	}
	if (cmd->argv[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		close_builtin_fds(cmd);
		return (1);
	}
	exit_code_long = ft_atol(cmd->argv[1]);
	exit_code = exit_code_long % 256;
	if (exit_code < 0)
		exit_code += 256;
	close_builtin_fds(cmd);
	exit(exit_code);
}
