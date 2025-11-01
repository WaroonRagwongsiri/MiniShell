/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 09:46:16 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/01 10:38:42 by waragwon         ###   ########.fr       */
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
		loop_out(cur);
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
		{
			cur->is_heredoc = true;
			cur->lim = cur_in->lim;
			heredoc(cur);
		}
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

t_infiles	*new_infile(char *filename, bool is_h, char *lim)
{
	t_infiles	*new;

	new = ft_safe_calloc(1, sizeof(t_infiles), "");
	if (!new)
		exit_msg("Malloc Err");
	new->filename = filename;
	new->is_heredoc = is_h;
	new->lim = lim;
	new->next = NULL;
	return (new);
}

t_outfiles	*new_outfile(char *filename, bool is_append)
{
	t_outfiles	*new;

	new = ft_safe_calloc(1, sizeof(t_outfiles), "");
	if (!new)
		exit_msg("Malloc Err");
	new->filename = filename;
	new->is_append = is_append;
	new->next = NULL;
	return (new);
}
