/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:17:50 by waragwon          #+#    #+#             */
/*   Updated: 2025/11/04 12:37:46 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

void	main_interrupt(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_crlf();
	rl_set_prompt(get_prompt(NULL));
	rl_redisplay();
	g_status = SIGINT;
}

void	child_interrupt(int signum)
{
	(void)signum;
	g_status = SIGINT;
}

void	child_quit(int signum)
{
	(void)signum;
	g_status = SIGQUIT;
}

static void	use_handler(t_sig_mode mode)
{
	if (mode == MAIN)
	{
		signal(SIGINT, main_interrupt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, child_interrupt);
		signal(SIGQUIT, child_quit);
	}
	else if (mode == MAIN_CHILD)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, heredoc_interrupt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == MAIN_HEREDOC)
	{
		signal(SIGINT, main_heredoc_interrupt);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	signal_handler(t_sig_mode mode)
{
	g_status = 0;
	use_handler(mode);
}
