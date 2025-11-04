/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:57:20 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 16:54:15 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int exec_cmd_wraper(t_cmd_group *cmd_lines, int process_num)
{
	if (cmd_lines == 0 || process_num == 0)
		return (0);
	if (process_num > MAX_PROCESS)
	{
		ft_putendl_fd("minishell: too many process", 2);
		return (1);
	}
	if (process_num - 1 > MAX_PIPE)
	{
		ft_putendl_fd("minishell: too many pipes", 2);
		return (1);
	}
	return (exec_cmd(cmd_lines, process_num));
}

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
		return (exec_cmd_wraper(cmd_lines, process_num));
	}
}
