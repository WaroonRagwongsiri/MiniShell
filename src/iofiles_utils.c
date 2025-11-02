/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofiles_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 09:46:16 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/02 13:55:17 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_in_access(char *filename, t_cmd_group *cur)
{
	if (!filename)
	{
		fd_error_once(filename, cur, ": No such file or directory");
		return (-1);
	}
	if (access(filename, F_OK) == -1)
	{
		fd_error_once(filename, cur, ": No such file or directory");
		return (-1);
	}
	if (access(filename, F_OK | R_OK) == -1)
	{
		fd_error_once(filename, cur, ": Permission denied");
		return (-1);
	}
	return (0);
}

int	check_out_access(char *filename, t_cmd_group *cur)
{
	if (!filename)
	{
		fd_error_once(filename, cur, ": No such file or directory");
		return (-1);
	}
	if (access(filename, W_OK) == -1)
	{
		fd_error_once(filename, cur, ": Permission denied");
		return (-1);
	}
	return (0);
}

void	fd_error_once(char *filename, t_cmd_group *cur, char *msg)
{
	if (!cur->is_error)
	{
		ft_putstr_fd(get_prompt(cur->env), 2);
		ft_putstr_fd(filename, 2);
		ft_putendl_fd(msg, 2);
	}
}
