/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:26:20 by waragwon          #+#    #+#             */
/*   Updated: 2025/11/03 16:17:34 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msg(char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	ft_safe_calloc(-1, -1, NULL);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	exit_cmd(char *cmd, char *err_msg, int exit_status)
{
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	ft_safe_calloc(-1, -1, NULL);
	rl_clear_history();
	exit(exit_status);
}

void	exit_errno(int exit_status)
{
	ft_safe_calloc(-1, -1, NULL);
	exit(exit_status);
}
