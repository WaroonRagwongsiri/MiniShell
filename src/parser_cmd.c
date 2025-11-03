/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:03:53 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 11:54:17 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_cmd_node(t_cmd_group *node, char *segment,
	char **env, int *exit_status)
{
	node->cmds_str = ft_strdup(segment);
	node->cmd_tokens = tokenizer(segment);
	tab_remove_quotes(node->cmd_tokens, '\"');
	expand_tokens(node->cmd_tokens, env, exit_status);
	tab_remove_quotes(node->cmd_tokens, '\'');
	node->in_filenames = get_in_filenames(node->cmd_tokens);
	node->out_filenames = get_out_filenames(node->cmd_tokens);
	node->cmd = get_cmd(node->cmd_tokens);
	node->argv = get_argv(node->cmd_tokens);
	node->env = env;
	node->is_heredoc = false;
	node->lim = NULL;
	node->in_files = NULL;
	node->out_files = NULL;
	node->is_error = false;
	set_in_files(node);
	set_out_files(node);
}

static void	link_cmd_node(t_cmd_group *cmds, int index, int size)
{
	cmds[index].operator = NONE;
	cmds[index].next = NULL;
	cmds[index].prev = NULL;
	if (index + 1 < size)
	{
		cmds[index].operator = PIPE;
		cmds[index].next = &cmds[index + 1];
	}
	if (index > 0)
		cmds[index].prev = &cmds[index - 1];
}

static t_cmd_group	*build_cmd_groups(char **segments, int size,
	char **env, int *exit_status)
{
	t_cmd_group	*cmd_group;
	int			i;

	cmd_group = ft_safe_calloc(size, sizeof(t_cmd_group), "");
	if (cmd_group == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		cmd_group[i].in_fd = STDIN_FILENO;
		cmd_group[i].out_fd = STDOUT_FILENO;
		cmd_group[i].h_pipe[0] = -1;
		cmd_group[i].h_pipe[1] = -1;
		init_cmd_node(&cmd_group[i], segments[i], env, exit_status);
		link_cmd_node(cmd_group, i, size);
		i++;
	}
	return (cmd_group);
}

t_cmd_group	*init_cmd_group(char *line, char **env, int *exit_status)
{
	char		**tab;
	t_cmd_group	*cmd_group;
	int			size;

	tab = ft_split(line, '|');
	size = tab_len(tab);
	if (size < 1)
		return (NULL);
	cmd_group = build_cmd_groups(tab, size, env, exit_status);
	return (cmd_group);
}
