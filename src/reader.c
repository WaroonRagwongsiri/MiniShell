/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:13:29 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 08:56:41 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
TODO : add dynamic prompt feature
*/
char	*get_prompt(char **env)
{
	char	*prompt;

	(void)env;
	prompt = ft_strdup("minishell : ");
	return (prompt);
}

char	*reader(char **env)
{
	char	*prompt;
	char	*line;

	prompt = get_prompt(env);
	if (prompt == NULL)
		return (NULL);
	line = readline(prompt);
	if (line == NULL)
		return (NULL);
	if (!is_completed_quotes(&line) && line == NULL)
	{
		line = ft_strdup("");
		if (line == NULL)
			return (NULL);
	}
	if (line != NULL && ft_strlen(line) > 0)
		add_history(line);
	return (line);
}
