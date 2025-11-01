/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_in_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:45:10 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/01 12:18:45 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_infiles	*find_last_infile(t_infiles *head)
{
	t_infiles	*curr;

	if (head == NULL)
		return (NULL);
	curr = head;
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}

static void	add_infile_to_list(t_cmd_group *node, char *filename,
	bool is_h, char *lim)
{
	t_infiles	*new_file;
	t_infiles	*last;

	new_file = new_infile(filename, is_h, lim);
	if (node->in_files == NULL)
		node->in_files = new_file;
	else
	{
		last = find_last_infile(node->in_files);
		last->next = new_file;
	}
}

static int	process_input_redirect(t_cmd_group *node, char **tokens, int i)
{
	if (tokens[i + 1] == NULL)
		return (i + 1);
	if (is_heredoc_token(tokens[i]))
	{
		add_infile_to_list(node, NULL, true, tokens[i + 1]);
		return (i + 2);
	}
	else if (is_simple_redirect(tokens[i], '<'))
	{
		add_infile_to_list(node, tokens[i + 1], false, NULL);
		return (i + 2);
	}
	return (i + 1);
}

void	set_in_files(t_cmd_group *node)
{
	int	i;

	i = 0;
	while (node->cmd_tokens[i] != NULL)
	{
		if (is_heredoc_token(node->cmd_tokens[i])
			|| is_simple_redirect(node->cmd_tokens[i], '<'))
			i = process_input_redirect(node, node->cmd_tokens, i);
		else
			i++;
	}
}
