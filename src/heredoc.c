/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:37:01 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/02 15:54:17 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_til_lim(t_cmd_group *cur)
{
	char	*line;

	line = readline("> ");
	while (line && ft_strncmp(line, cur->lim, ft_strlen(cur->lim) + 1) != 0
			&& g_status != SIGINT)
	{
		write(cur->h_pipe[1], line, ft_strlen(line));
		write(cur->h_pipe[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
}

int	heredoc(t_cmd_group *cur)
{
	if (pipe(cur->h_pipe) == -1)
		return (-1);
	read_til_lim(cur);
	cur->in_fd = cur->h_pipe[0];
	return (0);
}

void	loop_heredoc(t_cmd_group *cmd_lines)
{
	t_cmd_group	*cur;

	cur = cmd_lines;
	while (cur)
	{
		if (cur->is_heredoc == true)
			heredoc(cur);
		cur = cur->next;
	}
}
