/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:57:20 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 12:30:28 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_command(t_cmd_group *cmd_lines, char ***env_ptr)
{
	int			process_num;

	(void)env_ptr;
	process_num = cmd_len(cmd_lines);
	if (cmd_lines == NULL || process_num == 0)
		return (0);
	if (process_num == 1
		&& cmd_lines->argv != NULL
		&& cmd_lines->argv[0] != NULL
		&& is_builtin(cmd_lines->argv[0]))
	{
		loop_open(cmd_lines);
		return (execute_builtin(cmd_lines));
	}
	else
		return (exec_cmd(cmd_lines));
}
