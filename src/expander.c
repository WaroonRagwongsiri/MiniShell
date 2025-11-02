/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 08:33:10 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/02 09:01:54 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*expand_token(char *token, char **env, int *exit_status)
{
	char	*key;
	char	*value;

	if (token[0] == '$')
	{
		key = ft_strdup(token + 1);
		if (key[0] == '?')
			value = ft_itoa(*exit_status);
		else
			value = ft_getenv(env, key);
		if (value != NULL)
			return (value);
		return (NULL);
	}
	else
		return (NULL);
}

void	expand_tokens(char **tokens, char **env, int *exit_status)
{
	int		i;
	char	*expanded;

	if (tokens == NULL)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strchr(tokens[i], '$') != NULL)
		{
			expanded = expand_token(tokens[i], env, exit_status);
			if (expanded != NULL)
				tokens[i] = expanded;
		}
		i++;
	}
}
