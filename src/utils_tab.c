/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:33:26 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 20:08:55 by pioncha2         ###   ########.fr       */
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

static char	**free_partial(char **tab, int count)
{
	while (count > 0)
	{
		--count;
		free(tab[count]);
	}
	free(tab);
	return (NULL);
}

char	**append_tab(char **tab, char *str)
{
	char	**new_tab;
	int		i;
	int		size;

	if (str == NULL)
		return (tab);
	size = tab_len(tab);
	new_tab = malloc(sizeof(char *) * (size + 2));
	if (new_tab == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (new_tab[i] == NULL)
			return (free_partial(new_tab, i));
	}
	new_tab[i] = ft_strdup(str);
	if (new_tab[i] == NULL)
		return (free_partial(new_tab, i));
	new_tab[i + 1] = NULL;
	if (tab != NULL)
		free_tab(tab);
	return (new_tab);
}
