/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:44:02 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 15:43:19 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_cmd_group *cmd_lines)
{
	int			pid[MAX_PROCESS];
	int			pipes[MAX_PIPE][2];
	int			i;
	int			process_num;
	t_cmd_group	*cur;

	process_num = cmd_len(cmd_lines);
	if (cmd_lines == NULL || process_num == 0)
		return (0);
	if (open_pipes(pipes, process_num) == -1)
	{
		perror("Open Pipes");
		ft_safe_calloc(-1, -1, NULL);
		exit(EXIT_FAILURE);
	}
	i = -1;
	cur = cmd_lines;
	while (++i < process_num && cur)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("Fork Error");
			ft_safe_calloc(-1, -1, NULL);
			exit(EXIT_FAILURE);
		}
		if (pid[i] == 0)
		{
			dup_process(i, pipes, cur, process_num);
			close_pipes(pipes, process_num);
			close_all_fd(cmd_lines);
			execve(cur->cmd, cur->argv, cur->env);
			ft_safe_calloc(-1, -1, NULL);
			exit(EXIT_FAILURE);
		}
		cur = cur->next;
	}
	close_pipes(pipes, process_num);
	close_all_fd(cmd_lines);
	return (wait_pid_process(pid, process_num));
}

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

void	dup_process(int index_process, int pipes[MAX_PIPE][2],\
	t_cmd_group *cur, int process_num)
{
	if (index_process == 0)
	{
		dup2(cur->in_fd, STDIN_FILENO);
		dup2(pipes[index_process][1], STDOUT_FILENO);
	}
	else if (index_process == process_num - 1)
	{
		dup2(pipes[index_process - 1][0], STDIN_FILENO);
		dup2(cur->out_fd, STDOUT_FILENO);
	}
	else
	{
		dup2(pipes[index_process - 1][0], STDIN_FILENO);
		dup2(pipes[index_process][1], STDOUT_FILENO);
	}
}

int	wait_pid_process(int pid[MAX_PROCESS], int process_num)
{
	int	status[MAX_PROCESS];
	int	closed[MAX_PROCESS];
	int	closed_process;
	int	i;

	ft_bzero(closed, sizeof(closed));
	closed_process = 0;
	while (closed_process < process_num)
	{
		i = -1;
		while (++i < process_num)
		{
			if (closed[i])
				continue ;
			if (waitpid(pid[i], &status[i], WNOHANG) > 0)
			{
				WEXITSTATUS(status[i]);
				closed[i] = 1;
				closed_process++;
			}
		}
	}
	i = process_num;
	while (--i > 0 && status[i] == 0);
	return (status[i]);
}
