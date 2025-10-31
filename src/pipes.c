/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:44:02 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 21:11:25 by pioncha2         ###   ########.fr       */
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
		exit_msg("Pipe open Error");
	i = -1;
	cur = cmd_lines;
	while (++i < process_num && cur)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit_msg("Fork Error");
		if (pid[i] == 0)
			exec(i, pipes, cmd_lines, process_num);
		cur = cur->next;
	}
	close_all(pipes, process_num, cmd_lines);
	return (wait_pid_process(pid, process_num));
}

void	dup_process(int index, int pipes[MAX_PIPE][2],
	t_cmd_group *cur, int process_num)
{
	if (cur->in_fd != STDIN_FILENO)
	{
		if (dup2(cur->in_fd, STDIN_FILENO) == -1)
			exit_msg("Dup2 Input File");
	}
	else if (index > 0)
	{
		if (dup2(pipes[index - 1][0], STDIN_FILENO) == -1)
			exit_msg("Dup2 Pipe Input");
	}
	if (cur->out_fd != STDOUT_FILENO)
	{
		if (dup2(cur->out_fd, STDOUT_FILENO) == -1)
			exit_msg("Dup2 Output File");
	}
	else if (index < process_num - 1)
	{
		if (dup2(pipes[index][1], STDOUT_FILENO) == -1)
			exit_msg("Dup2 Pipe Output");
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
	while (--i > 0 && status[i] == 0)
		continue ;
	return (status[i]);
}

void	exec(int index, int pipes[MAX_PIPE][2],
	t_cmd_group *cmd_lines, int process_num)
{
	t_cmd_group	*cur;
	int			i;
	char		*cmd_path;

	i = -1;
	cur = cmd_lines;
	while (++i < index && cur)
		cur = cur->next;
	dup_process(index, pipes, cur, process_num);
	close_all(pipes, process_num, cmd_lines);
	cmd_path = ft_get_cmd_path(cur->cmd, cur->env);
	if (cmd_path == NULL)
	{
		ft_putstr_fd(cur->cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	execve(cmd_path, cur->argv, cur->env);
	perror(cur->cmd);
	free(cmd_path);
	exit(EXIT_FAILURE);
}
