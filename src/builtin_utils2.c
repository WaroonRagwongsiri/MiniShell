/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 07:56:23 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 20:48:55 by waroonwork@      ###   ########.fr       */
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

void	inner_unset(char *cur, char ***env_ptr)
{
	int		i;
	int		env_len;
	int		arg_len;

	i = -1;
	arg_len = ft_strlen(cur);
	env_len = tab_len(*env_ptr);
	while (++i < env_len)
	{
		if ((ft_strncmp((*env_ptr)[i], cur, arg_len) == 0
			&& (int)ft_strlen((*env_ptr)[i]) >= arg_len))
		{
			if (i == env_len - 1)
				(*env_ptr)[i] = NULL;
			else
				ft_memmove(&(*env_ptr)[i], &(*env_ptr)[i + 1],
					(env_len - i) * sizeof(char *));
			break ;
		}
	}
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env != NULL && env[i] != NULL)
	{
		j = i + 1;
		while (env[j] != NULL)
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_formatted_env(char *entry, int fd)
{
	int	i;

	ft_putstr_fd("declare -x ", fd);
	i = 0;
	while (entry[i] != '\0' && entry[i] != '=')
	{
		ft_putchar_fd(entry[i], fd);
		i++;
	}
	if (entry[i] == '\0')
	{
		ft_putchar_fd('\n', fd);
		return ;
	}
	ft_putstr_fd("=\"", fd);
	i++;
	while (entry[i] != '\0')
	{
		if (entry[i] == '\"' || entry[i] == '\\')
			ft_putchar_fd('\\', fd);
		ft_putchar_fd(entry[i], fd);
		i++;
	}
	ft_putstr_fd("\"\n", fd);
}
