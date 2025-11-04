/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:32:24 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 20:34:05 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (1);
}

int	export_assign(char *arg, char ***env_ptr)
{
	if (set_env_var(env_ptr, arg) != 0)
		return (-1);
	return (0);
}

int	export_without_value(char *arg, char ***env_ptr)
{
	if (find_env_index(*env_ptr, arg) != -1)
		return (0);
	if (append_env(env_ptr, arg) != 0)
		return (-1);
	return (0);
}

int	handle_export_arg(char *arg, char ***env_ptr)
{
	if (!is_valid_identifier(arg))
		return (export_error(arg));
	if (ft_strchr(arg, '=') != NULL)
		return (export_assign(arg, env_ptr));
	return (export_without_value(arg, env_ptr));
}

int	export_print_only(t_cmd_group *cmd, char ***env_ptr, int fd)
{
	print_env(*env_ptr, fd);
	close_builtin_fds(cmd);
	return (0);
}
