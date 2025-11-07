/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:47:18 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/07 20:11:31 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_exact(char *str, int digit_count)
{
	if (digit_count == 19)
	{
		if (str[0] == '-' && ft_strncmp(str, "-9223372036854775808", 22) > 0)
			return (false);
		if (str[0] != '-' && ft_strncmp(str, "9223372036854775807", 21) > 0)
			return (false);
	}
	return (true);
}

bool	is_valid_numeric(char *str)
{
	int	i;
	int	digit_count;

	if (str == NULL || *str == '\0')
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (false);
	digit_count = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		digit_count++;
		i++;
	}
	if (digit_count > 19)
		return (false);
	return (check_exact(str, digit_count));
}

int	get_exit_stats(int exit_status)
{
	static int	g_exit_status = 0;

	if (exit_status < 0)
		return (g_exit_status);
	g_exit_status = exit_status;
	return (g_exit_status);
}
