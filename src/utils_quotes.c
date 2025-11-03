/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 08:41:31 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 11:53:49 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	remove_quotes(char *str, char quote)
{
	int		i;
	int		j;

	if (str == NULL)
		return ;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
		{
			i++;
			while (str[i] != '\0' && str[i] != quote)
				str[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

void	tab_remove_quotes(char **tab, char quote)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		remove_quotes(tab[i], quote);
		i++;
	}
}
