/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:33:26 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/29 10:43:41 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab != NULL && tab[i] != NULL)
		i++;
	return (i);
}

char	**copy_tab(char **tab)
{
	int		size;
	int		i;
	char	**new_tab;

	size = tab_len(tab);
	new_tab = malloc(sizeof(char *) * (size + 1));
	if (new_tab == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

void	*free_tab(char **tab)
{
	int	i;

	if (tab != NULL)
	{
		i = 0;
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (NULL);
}
