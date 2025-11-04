/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 07:56:23 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 20:12:00 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_valid_identifier(char *arg)
{
	int		idx;

	if (arg == NULL || arg[0] == '\0' || arg[0] == '=' || ft_isdigit(arg[0]))
		return (false);
	idx = 0;
	while (arg[idx] != '\0' && arg[idx] != '=')
	{
		if (!ft_isalnum(arg[idx]) && arg[idx] != '_')
			return (false);
		idx++;
	}
	return (true);
}

int	find_env_index(char **env, char *arg)
{
	int	idx;
	int	key_len;

	key_len = 0;
	while (arg[key_len] != '\0' && arg[key_len] != '=')
		key_len++;
	idx = 0;
	while (env != NULL && env[idx] != NULL)
	{
		if (ft_strncmp(env[idx], arg, key_len) == 0
			&& env[idx][key_len] == '=')
			return (idx);
		idx++;
	}
	return (-1);
}

void	print_env(char **env, int fd)
{
	int		i;
	char	**sorted;

	sorted = copy_tab(env);
	if (sorted == NULL)
		return ;
	sort_env(sorted);
	i = 0;
	while (sorted[i] != NULL)
	{
		print_formatted_env(sorted[i], fd);
		i++;
	}
}

int	append_env(char ***env, char *arg)
{
	char	**new_env;
	int		size;
	int		i;

	size = tab_len(*env);
	new_env = ft_safe_calloc(size + 2, sizeof(char *), "");
	if (new_env == NULL)
		return (1);
	i = 0;
	while (i < size)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ft_strdup(arg);
	if (new_env[i] == NULL)
		return (1);
	new_env[i + 1] = NULL;
	*env = new_env;
	return (0);
}

int	set_env_var(char ***env, char *arg)
{
	int		idx;
	char	*dup;

	idx = find_env_index(*env, arg);
	if (idx >= 0)
	{
		dup = ft_strdup(arg);
		if (dup == NULL)
			return (1);
		(*env)[idx] = dup;
		return (0);
	}
	return (append_env(env, arg));
}
