/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 07:56:23 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 17:40:19 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_valid_echo_flag(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

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
