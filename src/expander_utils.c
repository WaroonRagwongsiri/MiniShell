/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:10:59 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/07 10:19:51 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_single_quote_condtion(char *token)
{
	int	i;
	int	cnt;

	i = 0;

	if (token == NULL)
		return (false);
	if (token[i] != '\'')
		return (false);
	i++;
	cnt = 1;
	while(token[i] != '\0')
	{
		if (token[i] == '\'')
			cnt++;
		i++;
	}
	if (i > 0 && cnt == 2 && token[i - 1] == '\'')
		return (true);
	return (false);
}
