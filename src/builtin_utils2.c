/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:25:57 by waragwon          #+#    #+#             */
/*   Updated: 2025/11/04 17:26:02 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	if (env == NULL || key == NULL || key[0] == '\0')
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			if (env[i][key_len] == '=')
				return (&env[i][key_len + 1]);
			else if (env[i][key_len] == '\0')
				return ("");
		}
		i++;
	}
	return (NULL);
}
