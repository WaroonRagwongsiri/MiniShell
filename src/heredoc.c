/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:37:01 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/02 18:03:36 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_til_lim(t_cmd_group *cur)
{
	char	*line;

	while (g_status != SIGINT)
	{
		line = readline("> ");
		if (g_status == SIGINT)
		{
			if (line)
				free(line);
			break ;
		}
		if (line == NULL)
		{
			heredoc_eof(cur);
			break ;
		}
		if (ft_strncmp(line, cur->lim, ft_strlen(cur->lim) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(cur->h_pipe[1], line, ft_strlen(line));
		write(cur->h_pipe[1], "\n", 1);
		free(line);
	}
}

int	heredoc(t_cmd_group *cur)
{
	signal_handler(HEREDOC);
	if (pipe(cur->h_pipe) == -1)
	{
		signal_handler(MAIN);
		return (-1);
	}
	read_til_lim(cur);
	if (g_status == SIGINT)
	{
		signal_handler(MAIN);
		return (-1);
	}
	close_fd(cur->h_pipe[1]);
	cur->in_fd = cur->h_pipe[0];
	signal_handler(MAIN);
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

void	heredoc_eof(t_cmd_group *cur)
{
	ft_putstr_fd(get_prompt(cur->env), 2);
	ft_putstr_fd("warning: here-document delimited by end-of-file ", 2);
	ft_putstr_fd(get_prompt(cur->env), 2);
	ft_putstr_fd("wanted: ", 2);
	ft_putendl_fd(cur->lim, 2);
}
