/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:11:04 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/07 15:15:55 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_skip_n_flag(char *arg)
{
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		if (is_valid_echo_flag(arg + 2))
			return (1);
	}
	return (0);
}

void	print_echo_args(t_cmd_group *cmd, int i, bool newline, int fd)
{
	while (cmd->argv[i] != NULL)
	{
		if (!newline && check_skip_n_flag(cmd->argv[i]))
		{
			i++;
			continue ;
		}
		ft_putstr_fd(cmd->argv[i], fd);
		if (cmd->argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
}
