/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:57:20 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 13:15:35 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_command(t_cmd_group *cmd_lines, char ***env_ptr)
{
	int			process_num;
	int			exit_status;

	(void)env_ptr;
	process_num = cmd_len(cmd_lines);
	if (cmd_lines == NULL || process_num == 0 || cmd_lines->cmd == NULL)
		return (0);
	if (process_num == 1
		&& cmd_lines->argv != NULL
		&& cmd_lines->argv[0] != NULL
		&& is_builtin(cmd_lines->argv[0]))
	{
		exit_status = loop_open(cmd_lines);
		if (exit_status != 0)
			return (exit_status);
		return (execute_builtin_main(cmd_lines));
	}
	else
	{
		exit_status = loop_open(cmd_lines);
		if (exit_status != 0)
			return (exit_status);
		return (exec_cmd(cmd_lines));
	}
}
