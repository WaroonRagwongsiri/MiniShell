/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:17:50 by waragwon          #+#    #+#             */
/*   Updated: 2025/11/02 14:59:00 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_crlf();
		rl_set_prompt(get_prompt(NULL));
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		continue ;
	else if (signum == SIGTSTP)
	{
		exit_msg("Stop");
	}
}
