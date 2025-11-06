/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:05:44 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/06 20:46:51 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define ERROR_MSG "minishell: syntax error near unexpected token `newline'\n"
#define PIPE_ERROR_MSG "minishell: syntax error near unexpected token `|'\n"

bool	is_heredoc_token(char *token)
{
	return (token != NULL && ft_strncmp(token, "<<", 3) == 0);
}

bool	is_append_token(char *token)
{
	return (token != NULL && ft_strncmp(token, ">>", 3) == 0);
}

bool	is_simple_redirect(char *token, char c)
{
	return (token != NULL && token[0] == c && token[1] == '\0');
}

bool	is_pipe_token(char *token)
{
	return (token != NULL && ft_strncmp(token, "|", 2) == 0);
}

// bool	is_valid_tokens(char *line)
// {
// 	char	**tokens;

// 	if (line == NULL)
// 		return (false);
// 	tokens = tokenizer(line);
// 	if (tab_len(tokens) == 1)
// 	{
// 		if (is_heredoc_token(tokens[0]) || is_append_token(tokens[0]))
// 		{
// 			ft_putstr_fd(ERROR_MSG, STDERR_FILENO);
// 			return (false);
// 		}
// 		if (is_simple_redirect(tokens[0], '<')
// 			|| is_simple_redirect(tokens[0], '>'))
// 		{
// 			ft_putstr_fd(ERROR_MSG, STDERR_FILENO);
// 			return (false);
// 		}
// 		if (is_pipe_token(tokens[0]))
// 		{
// 			ft_putstr_fd(PIPE_ERROR_MSG, STDERR_FILENO);
// 			return (false);
// 		}
// 	}
// 	return (true);
// }

bool	is_valid_tokens(char *line)
{
	char	**tokens;
	int		i;
	int		tok_len;

	if (line == NULL)
		return (false);
	tokens = tokenizer(line);
	i = -1;
	tok_len = tab_len(tokens);
	while (++i < tok_len)
	{
		if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			if (i == 0 || is_pipe_token(tokens[i - 1])
				|| is_append_token(tokens[i - 1])
				|| is_heredoc_token(tokens[i - 1])
				|| is_simple_redirect(tokens[i - 1], '<')
				|| is_simple_redirect(tokens[i - 1], '>'))
				return (false);
		}
	}
	return (true);
}
