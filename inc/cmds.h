/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:18:07 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 13:56:47 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# define MAX_PROCESS 50
# define MAX_PIPE 49

typedef struct s_io_files
{
	bool	is_rein;
	bool	is_reout;
	bool	is_heredoc;
	bool	is_append;
	int		fd_in;
	int		fd_out;
}	t_io_files;

typedef struct s_cmds
{
	char			*cmd;
	char			**argv;
	char			**env;
	t_io_files		io;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_shell
{
	char	**env;
	t_cmds	*cmd_lines;
	int		process_num;
}	t_shell;

t_cmds	*new_cmd(char **argvs, char **env);
int		cmd_len(t_cmds *cmds_lines);
int		exec_cmd(t_shell *shell);
int		open_pipes(int pipes[MAX_PIPE][2], int process_num);
void	close_pipes(int pipes[MAX_PIPE][2], t_cmds *cur, int process_num);
void	dup_process(int index_process, int pipes[MAX_PIPE][2],\
	t_cmds *cur, int process_num);
void	close_fd(int fd);
int		wait_pid_process(int pid[MAX_PROCESS], int process_num);

# endif