/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 08:33:10 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 12:26:40 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*expand_token(char *token, char ***env_ptr, int *exit_status)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (token[i] == ' ')
		i++;
	if (token[i] == '$')
	{
		key = ft_strdup(&token[i + 1]);
		key = ft_strtrim(key, " ");
		if (key[i] == '?')
			value = ft_itoa(*exit_status);
		else
			value = ft_getenv(*env_ptr, key);
		if (value != NULL)
			return (value);
		return (NULL);
	}
	else
		return (NULL);
}

void	expand_tokens(char **tokens, char ***env_ptr, int *exit_status)
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
			expanded = expand_token(tokens[i], env_ptr, exit_status);
			if (expanded != NULL)
				tokens[i] = expanded;
		}
		i++;
	}
}
