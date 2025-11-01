/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd_group.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:06:18 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/01 12:40:54 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	clean_infiles_list(t_infiles *in_files)
{
	t_infiles	*current;
	t_infiles	*next;

	current = in_files;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

static void	clean_outfiles_list(t_outfiles *out_files)
{
	t_outfiles	*current;
	t_outfiles	*next;

	current = out_files;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

static void	clean_cmd_node(t_cmd_group *node)
{
	if (node == NULL)
		return ;
	free(node->cmds_str);
	free_tab(node->cmd_tokens);
	free_tab(node->in_filenames);
	free_tab(node->out_filenames);
	free(node->cmd);
	free_tab(node->argv);
	close_fd(node->in_fd);
	close_fd(node->out_fd);
	if (node->is_heredoc)
	{
		close_fd(node->h_pipe[0]);
		close_fd(node->h_pipe[1]);
	}
	clean_infiles_list(node->in_files);
	clean_outfiles_list(node->out_files);
}

void	clean_cmd_group(t_cmd_group *node)
{
	t_cmd_group	*cur;
	t_cmd_group	*next;
	t_cmd_group	*base;

	if (node == NULL)
		return ;
	base = node;
	cur = node;
	while (cur != NULL)
	{
		next = cur->next;
		clean_cmd_node(cur);
		cur->next = NULL;
		cur->prev = NULL;
		cur = next;
	}
	free(base);
}
