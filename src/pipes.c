/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:44:02 by waragwon          #+#    #+#             */
/*   Updated: 2025/11/04 17:45:07 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_cmd_group *cmd_lines, int process_num)
{
	int			pid[MAX_PROCESS];
	int			pipes[MAX_PIPE][2];
	int			i;
	t_cmd_group	*cur;

	if (open_pipes(pipes, process_num) == -1)
		return (close_pipes(pipes, process_num), ft_putendl_fd(P_ERR, 2), 141);
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
	return (wait_pid_process(pid, process_num, cmd_lines));
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

void	exec(int index, int pipes[MAX_PIPE][2],
	t_cmd_group *cmd_lines, int process_num)
{
	t_cmd_group	*cur;
	int			i;
	char		*cmd_path;

	signal_handler(CHILD);
	i = -1;
	cur = cmd_lines;
	while (++i < index && cur)
		cur = cur->next;
	if (cur->is_error)
	{
		close_all(pipes, process_num, cmd_lines);
		exit_errno(cur->exit_status);
	}
	dup_process(index, pipes, cur, process_num);
	close_all(pipes, process_num, cmd_lines);
	if (cur->argv
		&& cur->argv[0]
		&& is_builtin(cur->argv[0]))
		exit_errno(execute_builtin(cur));
	cmd_path = find_cmd(cur->cmd, *(cur->env_ptr));
	if (cmd_path == NULL)
		exit_cmd(cur->cmd, ": command not found", 127);
	execve(cmd_path, cur->argv, *(cur->env_ptr));
	exit_msg("Execve");
}
