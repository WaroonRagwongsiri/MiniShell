/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:09:15 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 23:18:55 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_group	*simple_new_cmd(char **argv, char **env)
{
	t_cmd_group	*new;

	new = ft_safe_calloc(1, sizeof(t_cmd_group), "");
	if (!new)
		return (NULL);
	new->argv = argv;
	new->cmd = argv[0];
	new->env = env;
	new->in_filenames = NULL;
	new->out_filenames = NULL;
	new->operator = NONE;
	new->in_fd = STDIN_FILENO;
	new->out_fd = STDOUT_FILENO;
	new->next = NULL;
	new->prev = NULL;
	new->is_heredoc = false;
	new->h_pipe[0] = 0;
	new->h_pipe[1] = 1;
	new->lim = "EOF";
	return (new);
}

int	cmd_len(t_cmd_group *cmd_lines)
{
	t_cmd_group	*cur;
	int			len;

	len = 0;
	cur = cmd_lines;
	while (cur)
	{
		cur = cur->next;
		++len;
	}
	return (len);
}
