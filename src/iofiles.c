/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 09:46:16 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/03 12:36:23 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_open(t_cmd_group *cmd_lines)
{
	t_cmd_group	*cur;

	cur = cmd_lines;
	while (cur && g_status != SIGINT)
	{
		cur->exit_status = loop_in(cur);
		if (g_status == SIGINT)
			return (cur->exit_status);
		if (cur->exit_status == 0)
			cur->exit_status = loop_out(cur);
		cur = cur->next;
	}
	cur = cmd_lines;
	while (cur->next)
		cur = cur->next;
	return (cur->exit_status);
}

int	loop_in(t_cmd_group *cur)
{
	t_infiles	*cur_in;

	cur_in = cur->in_files;
	if (!cur_in)
		return (0);
	while (cur_in && g_status != SIGINT)
	{
		close_old(cur);
		if (check_in_access(cur_in->filename, cur) == -1)
		{
			cur->is_error = true;
			cur_in = cur_in->next;
			continue ;
		}
		if (cur_in->is_heredoc)
		{
			cur->is_heredoc = true;
			cur->lim = cur_in->lim;
			if (heredoc(cur) != 0)
			{
				cur->is_error = true;
				return (130);
			}
		}
		else
		{
			cur->is_heredoc = false;
			cur->in_fd = open(cur_in->filename, O_RDONLY);
		}
		cur_in = cur_in->next;
	}
	cur_in = cur->in_files;
	while (cur_in->next)
		cur_in = cur_in->next;
	return (cur->is_error);
}

int	loop_out(t_cmd_group *cur)
{
	t_outfiles	*cur_out;

	cur_out = cur->out_files;
	if (!cur_out)
		return (0);
	while (cur_out && g_status != SIGINT)
	{
		close_fd(cur->out_fd);
		if (cur_out->is_append)
			cur->out_fd = open(cur_out->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cur->out_fd = open(cur_out->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cur->out_fd == -1)
		{
			check_out_access(cur_out->filename, cur);
			cur->is_error = true;
			return (1);
		}
		cur_out = cur_out->next;
	}
	return (0);
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
