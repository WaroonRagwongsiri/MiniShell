/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:15:49 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 20:37:09 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_env_main(t_cmd_group *cmd)
{
	int		i;
	char	**env;

	i = 0;
	env = *(cmd->env_ptr);
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '=') != NULL)
			ft_putendl_fd(env[i], cmd->out_fd);
		i++;
	}
	close_builtin_fds(cmd);
	return (0);
}

int	builtin_export_main(t_cmd_group *cmd, char ***env_ptr)
{
	int	i;
	int	status;
	int	result;

	if (cmd->argv[1] == NULL)
		return (export_print_only(cmd, env_ptr, cmd->out_fd));
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

int	builtin_unset_main(t_cmd_group *cmd, char ***env_ptr)
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
