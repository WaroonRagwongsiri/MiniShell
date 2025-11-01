/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd_group.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:06:18 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/01 11:15:31 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	clean_cmd_node(t_cmd_group *node)
{
	if (node == NULL)
		return ;
	free(node->cmds_str);
	node->cmds_str = NULL;
	free_tab(node->cmd_tokens);
	node->cmd_tokens = NULL;
	free_tab(node->in_filenames);
	node->in_filenames = NULL;
	free_tab(node->out_filenames);
	node->out_filenames = NULL;
	free(node->cmd);
	node->cmd = NULL;
	free_tab(node->argv);
	node->argv = NULL;
	close_fd(node->in_fd);
	close_fd(node->out_fd);
	node->in_fd = STDIN_FILENO;
	node->out_fd = STDOUT_FILENO;
	node->env = NULL;
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
