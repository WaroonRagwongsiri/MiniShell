/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 09:46:16 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/01 09:55:33 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_open(t_cmd_group *cmd_lines)
{
	t_cmd_group	*cur;

	cur = cmd_lines;
	while (cur)
	{
		loop_in(cur);
		cur = cur->next;
	}
}

void	loop_in(t_cmd_group *cur)
{
	t_infiles	*cur_in;

	cur_in = cur->in_files;
	while (cur_in)
	{
		close_fd(cur->in_fd);
		if (cur_in->is_heredoc)
			heredoc(cur);
		else
			cur->in_fd = open(cur_in->filename, O_RDONLY);
		cur_in = cur_in->next;
	}
}

void	loop_out(t_cmd_group *cur)
{
	t_outfiles	*cur_out;

	cur_out = cur->out_files;
	while (cur_out)
	{
		close_fd(cur->out_fd);
		if (cur_out->is_append)
			cur->out_fd = open(cur_out->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cur->out_fd = open(cur_out->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		cur_out = cur_out->next;
	}
}
