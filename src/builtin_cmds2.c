/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:15:49 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 20:34:20 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_builtin_fds(t_cmd_group *cmd)
{
	close_fd(cmd->in_fd);
	close_fd(cmd->out_fd);
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
}

int	builtin_env(t_cmd_group *cmd)
{
	int		i;
	char	**env;

	i = 0;
	env = *(cmd->env_ptr);
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '=') != NULL)
			ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
	close_builtin_fds(cmd);
	return (0);
}

int	builtin_export(t_cmd_group *cmd, char ***env_ptr)
{
	int	i;
	int	status;
	int	result;

	if (cmd->argv[1] == NULL)
		return (export_print_only(cmd, env_ptr, STDOUT_FILENO));
	i = 1;
	status = 0;
	while (cmd->argv[i] != NULL)
	{
		result = handle_export_arg(cmd->argv[i], env_ptr);
		if (result == -1)
			return (close_builtin_fds(cmd), 1);
		if (result > 0)
			status = result;
		i++;
	}
	close_builtin_fds(cmd);
	return (status);
}

int	builtin_unset(t_cmd_group *cmd, char ***env_ptr)
{
	int		i;

	i = 1;
	while (cmd->argv[i])
	{
		inner_unset(cmd->argv[i], env_ptr);
		i++;
	}
	close_builtin_fds(cmd);
	return (0);
}
