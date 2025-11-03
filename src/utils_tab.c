/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:33:26 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 19:52:58 by pioncha2         ###   ########.fr       */
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
	new_tab = ft_safe_calloc(size + 1, sizeof(char *), "copy_tab");
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
	(void)tab;
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
	new_tab = ft_safe_calloc(size + 2, sizeof(char *), "append_tab");
	if (new_tab == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (new_tab[i] == NULL)
			return (NULL);
	}
	new_tab[i] = ft_strdup(str);
	if (new_tab[i] == NULL)
		return (NULL);
	new_tab[i + 1] = NULL;
	return (new_tab);
}

char	**split_tokens(char **str)
{
	int		i;
	int		j;
	char	**new_tab;
	char	*temp;

	new_tab = ft_safe_calloc(tab_len(str) + 1, sizeof(char *), "");
	i = 0;
	j = 0;
	temp = ft_strdup("");
	while (str[j] != NULL)
	{
		if (ft_strncmp(str[j], "|", 2) != 0)
		{
			temp = ft_strjoin(temp, " ");
			temp = ft_strjoin(temp, str[j]);
		}
		else
		{
			new_tab[i++] = ft_strdup(temp);
			temp = ft_strdup("");
		}
		j++;
	}
	new_tab[i] = ft_strdup(temp);
	return (new_tab);
}
