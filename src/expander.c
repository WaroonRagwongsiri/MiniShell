/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 08:33:10 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 16:15:43 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*expand_token(char *token, char ***env_ptr, int *exit_status)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (token[i] == '\'')
		return (NULL);
	while (token[i] == ' ' || token[i] == '\"' || token[i] == '\'')
		i++;
	if (token[i] == '$')
	{
		key = ft_strdup(&token[i + 1]);
		key = ft_strtrim(key, "\'\" ");
		if (key[0] == '?')
			value = ft_strjoin(ft_itoa(*exit_status), ft_strdup(&token[i + 2]));
		else
			value = ft_getenv(*env_ptr, key);
		if (value != NULL)
			return (value);
		return (ft_strdup(""));
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

char	*join_tokens(char **tokens)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strdup("");
	while (tokens[i] != NULL)
	{
		new = ft_strjoin(new, " ");
		new = ft_strjoin(new, tokens[i]);
		i++;
	}
	return (new);
}
