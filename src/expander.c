/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 08:33:10 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 18:49:08 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_strjoin_char1(char *str, char c)
{
	char	*res;
	int		i;

	res = ft_safe_calloc(ft_strlen(str) + 2, sizeof(char), "");
	i = 0;
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	i++;
	res[i] = '\0';
	return (res);
}

static char	*expand_variable(char *token, int *i,
		char ***env_ptr, int *exit_status)
{
	int		start;
	char	*key;
	char	*value;

	if (token[*i] == '\0')
		return (ft_strdup(""));
	if (token[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(*exit_status));
	}
	start = *i;
	while (token[*i] != '\0' && (ft_isalnum(token[*i]) || token[*i] == '_'))
		(*i)++;
	key = ft_substr(token, start, *i - start);
	if (key == NULL)
		return (NULL);
	if (key[0] == '\0')
		return (ft_strdup(""));
	value = ft_getenv(*env_ptr, key);
	if (value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static int	is_expandable_char(char c)
{
	if (c == '\0')
		return (0);
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

static char	*expand_token(char *token, char ***env_ptr, int *exit_status)
{
	char	*expanded;
	char	*addition;
	int		i;

	if (token[0] == '\'')
		return (NULL);
	remove_quotes(token);
	expanded = ft_strdup("");
	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] != '$')
			expanded = ft_strjoin_char1(expanded, token[i++]);
		else if (!is_expandable_char(token[i + 1]))
			expanded = ft_strjoin_char1(expanded, token[i++]);
		else
		{
			i++;
			addition = expand_variable(token, &i, env_ptr, exit_status);
			if (addition == NULL)
				return (NULL);
			expanded = ft_strjoin(expanded, addition);
		}
	}
	return (expanded);
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
