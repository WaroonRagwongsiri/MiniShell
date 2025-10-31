/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:18:07 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 16:58:20 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# define MAX_PROCESS 50
# define MAX_PIPE 49

typedef struct s_cmd_group
{
	char				*cmds_str;
	char				**cmd_tokens;
	char				**in_filenames;
	char				**out_filenames;
	char				*cmd;
	char				**argv;
	char				**env;
	char				*operator;
	int					in_fd;
	int					out_fd;
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

#endif