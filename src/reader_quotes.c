/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 08:53:52 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 16:07:40 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	has_unclosed_quotes(char *str, char *quote)
{
	bool	in_single;
	bool	in_double;
	int		i;

	in_single = false;
	in_double = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single)
			in_double = !in_double;
		i++;
	}
	if (in_single && quote != NULL)
		*quote = '\'';
	if (in_double && quote != NULL)
		*quote = '\"';
	return (in_single || in_double);
}

static char	*quote_prompt(char missing)
{
	if (missing == '\'')
		return ("quote> ");
	return ("dquote> ");
}

static char	*append_line(char *curr, char *next)
{
	char	*with_newline;
	char	*joined;

	with_newline = ft_strjoin(curr, "\n");
	if (with_newline == NULL)
		return (NULL);
	joined = ft_strjoin(with_newline, next);
	if (joined == NULL)
		return (NULL);
	return (joined);
}

static bool	read_and_append(char **line, char missing_quote)
{
	char	*next_line;
	char	*temp_next_line;
	char	*merged;

	next_line = readline(quote_prompt(missing_quote));
	if (next_line == NULL)
		return (false);
	temp_next_line = ft_strdup(next_line);
	free(next_line);
	merged = append_line(*line, temp_next_line);
	if (merged == NULL)
	{
		*line = NULL;
		return (false);
	}
	*line = merged;
	return (true);
}

bool	is_completed_quotes(char **line)
{
	char	missing_quote;

	if (line == NULL || *line == NULL)
		return (true);
	while (has_unclosed_quotes(*line, &missing_quote))
		if (!read_and_append(line, missing_quote))
			return (false);
	return (true);
}
