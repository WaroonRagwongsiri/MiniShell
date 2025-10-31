/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:00:08 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 10:15:28 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_quotation_mark(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_special_char(char c)
{
	if (is_whitespace(c))
		return (true);
	if (c == '|' || c == '&')
		return (true);
	if (c == '(' || c == ')')
		return (true);
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_redirect_char(char c)
{
	return (c == '<' || c == '>');
}
