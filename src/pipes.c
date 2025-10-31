/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:19:32 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 13:57:03 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_shell *shell)
{
	int		pid[MAX_PROCESS];
	int		pipes[MAX_PIPE][2];
	int		i;
	t_cmds	*cur;

	if (open_pipes(pipes, shell->process_num) == -1)
	{
		perror("Open Pipes");
		exit(EXIT_FAILURE);
	}
	i = -1;
	cur = shell->cmd_lines;
	while (++i < shell->process_num)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("Fork Error");
			exit(EXIT_FAILURE);
		}
		if (pid[i] == 0)
		{
			dup_process(i, pipes, cur, shell->process_num);
			close_pipes(pipes, cur, shell->process_num);
			execve(cur->cmd, cur->argv, shell->env);
			exit(EXIT_SUCCESS);
		}
	}
	close_pipes(pipes, cur, shell->process_num);
	return (wait_pid_process(pid, shell->process_num));
}

int	open_pipes(int pipes[MAX_PIPE][2], int process_num)
{
	int	i;

	i = -1;
	while (++i < process_num - 1)
	{
		if (pipe(pipes[i]) == -1)
			return (-1);
	}
	return (0);
}

void	close_pipes(int pipes[MAX_PIPE][2], t_cmds *cur, int process_num)
{
	int	i;

	i = 0;
	while (i < process_num - 1)
	{
		close_fd(pipes[i][0]);
		close_fd(pipes[i][1]);
		i++;
	}
	close_fd(cur->io.fd_in);
	close_fd(cur->io.fd_out);
}

void	dup_process(int index_process, int pipes[MAX_PIPE][2],\
	t_cmds *cur, int process_num)
{
	if (index_process == 0)
	{
		dup2(cur->io.fd_in, STDIN_FILENO);
		dup2(pipes[index_process][1], STDOUT_FILENO);
	}
	else if (index_process == process_num - 1)
	{
		dup2(pipes[index_process - 1][0], STDIN_FILENO);
		dup2(cur->io.fd_out, STDOUT_FILENO);
	}
	else
	{
		dup2(pipes[index_process - 1][0], STDIN_FILENO);
		dup2(pipes[index_process][1], STDOUT_FILENO);
	}
}

void	close_fd(int fd)
{
	if (fd > 2)
		close(fd);
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
