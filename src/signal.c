/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:17:50 by waragwon          #+#    #+#             */
/*   Updated: 2025/11/02 14:32:11 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

void	handler(int signum)
{
	if (signum == SIGINT)
		exit_msg("Interrupt");
	else if (signum == SIGQUIT)
		exit_msg("Quit");
	else if (signum == SIGTSTP)
		exit_msg("Stop");
}
