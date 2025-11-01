/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:05:44 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/01 11:06:09 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
