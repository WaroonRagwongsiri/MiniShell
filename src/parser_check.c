/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:05:44 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/07 20:59:05 by waragwon         ###   ########.fr       */
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
		if (!is_valid_pipes(tokens, i))
		{
			ft_putendl_fd("syntax error near unexpected token `|'", 2);
			return (false);
		}
		else if (!is_valid_redirect(tokens, i))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
			put_err_parese_redirect(tokens[i + 1]);
			return (false);
		}
	}
	return (true);
}
