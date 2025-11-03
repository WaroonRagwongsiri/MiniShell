/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:03:53 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 22:12:53 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**tab_skip_empty(char **tab)
{
	int	i;

	if (tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL && ft_strlen(tab[i]) == 0)
		i++;
	if (i != 0)
		tab = copy_tab(&tab[i]);
	return (tab);
}

static void	init_cmd_node(t_cmd_group *node, char *segment,
	char ***env_ptr, int *exit_status)
{
	node->cmds_str = ft_strdup(segment);
	node->cmd_tokens = tokenizer(segment);
	expand_tokens(node->cmd_tokens, env_ptr, exit_status);
	tab_remove_quotes(node->cmd_tokens);
	node->cmd_tokens = tab_skip_empty(node->cmd_tokens);
	node->in_filenames = get_in_filenames(node->cmd_tokens);
	node->out_filenames = get_out_filenames(node->cmd_tokens);
	node->argv = get_argv(node->cmd_tokens);
	node->cmd = ft_strdup(node->argv[0]);
	node->env_ptr = env_ptr;
	node->is_heredoc = false;
	node->lim = NULL;
	node->in_files = NULL;
	node->out_files = NULL;
	node->is_error = false;
	node->exit_status = 0;
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
	char ***env_ptr, int *exit_status)
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
		init_cmd_node(&cmd_group[i], segments[i], env_ptr, exit_status);
		link_cmd_node(cmd_group, i, size);
		i++;
	}
	return (cmd_group);
}

t_cmd_group	*init_cmd_group(char *line, char ***env_ptr, int *exit_status)
{
	char		**tab;
	t_cmd_group	*cmd_group;
	int			size;
	char		**tokens;

	tokens = tokenizer(line);
	tab = split_tokens(tokens);
	size = tab_len(tab);
	if (size < 1)
		return (NULL);
	cmd_group = build_cmd_groups(tab, size, env_ptr, exit_status);
	return (cmd_group);
}
