/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:26:20 by waragwon          #+#    #+#             */
/*   Updated: 2025/11/02 09:10:37 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	ft_safe_calloc(-1, -1, NULL);
	//rl_clear_history();
	clear_history(); // for macos
	exit(EXIT_FAILURE);
}

void	exit_cmd(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	ft_safe_calloc(-1, -1, NULL);
	//rl_clear_history();
	clear_history(); // for macos
	exit(127);
}
