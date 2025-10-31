/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:03:46 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 21:12:10 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_in_filenames(char **tab)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], "<", 1) == 0)
		{
			if (tab[i + 1] != NULL)
				res = append_tab(res, tab[i + 1]);
			i += 2;
		}
		else
			i++;
	}
	return (res);
}

char	**get_out_filenames(char **tab)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], ">", 1) == 0 || ft_strncmp(tab[i], ">>", 2) == 0)
		{
			if (tab[i + 1] != NULL)
				res = append_tab(res, tab[i + 1]);
			i += 2;
		}
		else
			i++;
	}
	return (res);
}

char	*get_cmd(char **tab)
{
	if (tab == NULL || tab[0] == NULL)
		return (NULL);
	return (ft_strdup(tab[0]));
}

char	**get_argv(char **tab)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (tab != NULL && tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], ">", 1) == 0 || ft_strncmp(tab[i], "<", 1) == 0)
		{
			if (tab[i + 1] != NULL)
				i += 2;
			else
				i++;
		}
		else
			res = append_tab(res, tab[i++]);
	}
	return (res);
}
