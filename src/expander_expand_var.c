/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_expand_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:41:36 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/07 13:03:31 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*handle_exit_status(int *i, int *exit_status, bool *in_single)
{
	(*i)++;
	if (!(*in_single))
		return (ft_itoa(*exit_status));
	return (ft_strdup("$?"));
}

static char	*extract_key(char *token, int *i)
{
	int		start;
	char	*key;

	start = *i;
	while (token[*i] != '\0' && (ft_isalnum(token[*i]) || token[*i] == '_'))
		(*i)++;
	key = ft_substr(token, start, *i - start);
	return (key);
}

static char	*get_var_value(char *key, char ***env_ptr, bool *in_single)
{
	char	*value;

	if (*in_single)
		return (ft_strjoin(ft_strdup("$"), ft_strdup(key)));
	value = ft_getenv(*env_ptr, key);
	if (value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_variable(char *token, int *i,
	char ***env_ptr, t_exp_tmp params)
{
	char	*key;

	if (token[*i] == '\0')
		return (ft_strdup(""));
	if (token[*i] == '?')
		return (handle_exit_status(i, params.exit_status, params.in_single));
	key = extract_key(token, i);
	if (key == NULL)
		return (NULL);
	if (key[0] == '\0')
		return (ft_strdup(""));
	return (get_var_value(key, env_ptr, params.in_single));
}
