/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:15:49 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 20:12:27 by pioncha2         ###   ########.fr       */
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

static int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (1);
}

int	builtin_export_main(t_cmd_group *cmd, char ***env_ptr)
{
	int	i;
	int	status;

	if (cmd->argv[1] == NULL)
	{
		print_env(*env_ptr, cmd->out_fd);
		close_builtin_fds(cmd);
		return (0);
	}
	i = 1;
	status = 0;
	while (cmd->argv[i] != NULL)
	{
		if (!is_valid_identifier(cmd->argv[i]))
			status = export_error(cmd->argv[i]);
		else if (ft_strchr(cmd->argv[i], '=') != NULL
			&& set_env_var(env_ptr, cmd->argv[i]) != 0)
			return (close_builtin_fds(cmd), 1);
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
