/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:16:55 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/05 11:21:38 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_empty_cmds(char	*str)
{
	int	i;

	if (str == NULL)
		return (1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
