/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:18:07 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 12:34:43 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

typedef struct s_shell
{
	char	**env;
	t_cmds	*cmd_lines;
}	t_shell;

typedef struct s_cmds
{
	char		*cmd;
	char		**argv;
	char		**env;
	t_io_files	io;
	t_cmds		*next;
}	t_cmds;

typedef struct s_io_files
{
	bool	is_rein;
	bool	is_reout;
	bool	is_heredoc;
	bool	is_append;
	int		fd_in;
	int		fd_out;
}	t_io_files;

# endif