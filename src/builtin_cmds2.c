/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:15:49 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/01 23:17:58 by waroonwork@      ###   ########.fr       */
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
	int	i;
	int	env_len;
	int	arg_len;

	if (cmd->argv[1] == NULL)
		return (0);
	env_len = tab_len(*env);
	i = -1;
	arg_len = ft_strlen(cmd->argv[1]);
	while (++i < env_len)
	{
		if ((ft_strncmp((*env)[i], cmd->argv[1], arg_len) == 0 && 
				(int)ft_strlen((*env)[i]) >= arg_len && 
				(*env)[i][arg_len] == '='))
		{
			if (i == env_len - 1)
				(*env)[i] = NULL;
			else
				ft_memmove(&(*env)[i], &(*env)[i + 1], (env_len - i) * sizeof(char *));
			break ;
		}
	}
	close_builtin_fds(cmd);
	return (0);
}
