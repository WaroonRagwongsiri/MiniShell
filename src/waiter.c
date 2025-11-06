/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:31:25 by waragwon          #+#    #+#             */
/*   Updated: 2025/11/05 22:32:38 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_pid_process(int pid[MAX_PROCESS], int process_num,
	t_cmd_group *cmd_lines)
{
	int	status;

	signal_handler(MAIN_CHILD);
	status = inner_wait_process(pid, process_num, cmd_lines, 0);
	signal_handler(MAIN);
	print_sig_exit(status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	inner_wait_process(int pid[MAX_PROCESS], int process_num,
	t_cmd_group *cmd_lines, int closed_process)
{
	int			status[MAX_PROCESS];
	int			closed[MAX_PROCESS];
	t_cmd_group	*cur;
	int			i;

	ft_bzero(closed, sizeof(closed));
	while (closed_process < process_num)
	{
		i = -1;
		cur = cmd_lines;
		while (++i < process_num)
		{
			if (closed[i])
				continue ;
			if (waitpid(pid[i], &status[i], WNOHANG) > 0)
			{
				closed[i] = 1;
				closed_process++;
				cur->exit_status = status[i];
			}
			cur = cur->next;
		}
	}
	return (status[process_num - 1]);
}

void	print_sig_exit(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putendl_fd("", 2);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		else if (WTERMSIG(status) == SIGSEGV)
			ft_putendl_fd("Segmentation fault (core dumped)", 2);
	}
}
