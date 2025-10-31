/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:18:07 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 20:15:33 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# define MAX_PROCESS 50
# define MAX_PIPE 49

// Error Msg
# define PIPE_ERR "Pipe Open Error"

typedef enum s_operator
{
	NONE,
	PIPE,
}	t_operator;

typedef struct s_cmd_group
{
	char				*cmds_str;
	char				**cmd_tokens;
	char				**in_filenames;
	char				**out_filenames;
	char				*cmd;
	char				**argv;
	char				**env;
	t_operator			operator;
	int					in_fd;
	int					out_fd;
	bool				is_heredoc;
	int					h_pipe[2];
	char				*lim;
	struct s_cmd_group	*next;
	struct s_cmd_group	*prev;
}	t_cmd_group;

t_cmd_group	*simple_new_cmd(char **argv, char **env);
int			cmd_len(t_cmd_group *cmd_lines);
int			exec_cmd(t_cmd_group *cmd_lines);
void		close_fd(int fd);
int			open_pipes(int pipes[MAX_PIPE][2], int process_num);
void		close_pipes(int pipes[MAX_PIPE][2], int process_num);
void		close_all_fd(t_cmd_group *cmd_lines);
void		dup_process(int index, int pipes[MAX_PIPE][2],
				t_cmd_group *cur, int process_num);
int			wait_pid_process(int pid[MAX_PROCESS], int process_num);
void		close_all(int pipes[MAX_PIPE][2], int process_num,
				t_cmd_group *cmd_lines);
void		exec(int index, int pipes[MAX_PIPE][2],
				t_cmd_group *cmd_lines, int process_num);
int			heredoc(t_cmd_group *cur);
void		read_til_lim(t_cmd_group *cur);
void		loop_heredoc(t_cmd_group *cmd_lines);

#endif