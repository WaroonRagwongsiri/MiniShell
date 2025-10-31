/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:25:24 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 16:33:14 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int fd)
{
	if (fd > 2)
		close(fd);
}

int	open_pipes(int pipes[MAX_PIPE][2], int process_num)
{
	int	i;

	i = 0;
	while (i < process_num - 1)
	{
		if (pipe(pipes[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	close_pipes(int pipes[MAX_PIPE][2], int process_num)
{
	int	i;

	i = 0;
	while (i < process_num - 1)
	{
		close_fd(pipes[i][0]);
		close_fd(pipes[i][1]);
		i++;
	}
}

void	close_all_fd(t_cmd_group *cmd_lines)
{
	t_cmd_group	*cur;

	cur = cmd_lines;
	while (cur)
	{
		close_fd(cur->in_fd);
		close_fd(cur->out_fd);
		cur = cur->next;
	}
}

void	close_all(int pipes[MAX_PIPE][2], int process_num,
	t_cmd_group *cmd_lines)
{
	close_pipes(pipes, process_num);
	close_all_fd(cmd_lines);
}
