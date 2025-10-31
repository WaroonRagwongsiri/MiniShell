/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:25:22 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/30 20:21:37 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **args, char **env)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (builtin_echo(args));
	if (ft_strncmp(args[0], "cd", 3) == 0)
		return (builtin_cd(args, env));
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (builtin_exit(args));
	if (ft_strncmp(args[0], "env", 4) == 0)
		return (builtin_env(env));
	if (ft_strncmp(args[0], "export", 7) == 0)
		return (builtin_export(args, &env));
	if (ft_strncmp(args[0], "unset", 6) == 0)
		return (builtin_unset(args, &env));
	return (1);
}
