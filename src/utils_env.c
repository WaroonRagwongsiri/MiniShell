/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:58:30 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 13:52:14 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_getenv(char **env, char *key)
{
	int	i;
	int	len_key;

	if (env == NULL || key == NULL)
		return (NULL);
	i = 0;
	len_key = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, len_key) == 0)
		{
			if (env[i][len_key] == '=')
				return (&env[i][len_key + 1]);
		}
		i++;
	}
	return (NULL);
}
