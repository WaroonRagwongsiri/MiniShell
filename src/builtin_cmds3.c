/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:06:05 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/07 20:04:57 by waragwon         ###   ########.fr       */
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
	print_echo_args(cmd, i, newline, cmd->out_fd);
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

int	builtin_cd_main(t_cmd_group *cmd)
{
	char	*path;
	char	*oldpwd;
	int		status;

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
	oldpwd = ft_getenv(*(cmd->env_ptr), "OLDPWD");
	status = handle_cd(cmd, path, oldpwd, cmd->out_fd);
	close_builtin_fds(cmd);
	return (status);
}

int	builtin_exit_main(t_cmd_group *cmd)
{
	long	exit_code_long;
	int		exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->argv[1] == NULL || ft_strncmp(cmd->argv[1], "--", 3) == 0)
		exit(get_exit_stats(-1));
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
