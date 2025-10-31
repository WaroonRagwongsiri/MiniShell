/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:26:20 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 22:33:00 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	ft_safe_calloc(-1, -1, NULL);
	exit(EXIT_FAILURE);
}

void	exit_cmd(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	ft_safe_calloc(-1, -1, NULL);
	exit(127);
}
