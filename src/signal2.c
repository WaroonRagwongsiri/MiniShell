/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:21:51 by waragwon          #+#    #+#             */
/*   Updated: 2025/11/04 12:22:16 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_interrupt(int signum)
{
	(void)signum;
	g_status = SIGINT;
	rl_replace_line("", 0);
	rl_crlf();
	rl_redisplay();
	exit_errno(130);
}

void	main_heredoc_interrupt(int signum)
{
	(void)signum;
	g_status = SIGINT;
}
