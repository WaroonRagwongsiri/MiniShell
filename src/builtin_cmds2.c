/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:15:49 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/01 19:10:12 by pioncha2         ###   ########.fr       */
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

int	builtin_export(t_cmd_group *cmd, char ***env)
{
	(void)env;
	ft_putendl_fd("TODO : Export !", cmd->out_fd);
	close_builtin_fds(cmd);
	return (0);
}

int	builtin_unset(t_cmd_group *cmd, char ***env)
{
	(void)env;
	ft_putendl_fd("TODO : Unset !", cmd->out_fd);
	close_builtin_fds(cmd);
	return (0);
}
