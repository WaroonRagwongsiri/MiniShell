/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 08:33:10 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/07 13:17:17 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_expandable_char(char c)
{
	if (c == '\0')
		return (0);
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

char	*ft_strjoin_char1(char *str, char c)
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
