/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_expand_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:59:30 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/07 13:19:05 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	update_quote_status(char c, bool *in_single, bool *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	if (c == '\"' && !(*in_single))
		*in_double = !(*in_double);
}

static char	*handle_dollar_sign(char *token, int *i, char ***env_ptr,
	t_exp_tmp params)
{
	char	*addition;

	if (!is_expandable_char(token[*i + 1]))
		return (ft_strjoin_char1(ft_strdup(""), token[(*i)++]));
	(*i)++;
	addition = expand_variable(token, i, env_ptr, params);
	return (addition);
}

static char	*process_char(char *expanded, char *token, int *i,
	t_exp_tmp params)
{
	char	*addition;

	update_quote_status(token[*i], params.in_single, params.in_double);
	if (token[*i] != '$')
		return (ft_strjoin_char1(expanded, token[(*i)++]));
	addition = handle_dollar_sign(token, i, (params.env_ptr), params);
	if (addition == NULL)
		return (NULL);
	return (ft_strjoin(expanded, addition));
}

char	*expand_token(char *token, char ***env_ptr, int *exit_status)
{
	char			*expanded;
	int				i;
	bool			in_single;
	bool			in_double;
	t_exp_tmp		params;

	expanded = ft_strdup("");
	i = 0;
	in_single = false;
	in_double = false;
	params.in_single = &in_single;
	params.in_double = &in_double;
	params.exit_status = exit_status;
	params.env_ptr = env_ptr;
	while (token[i] != '\0')
	{
		expanded = process_char(expanded, token, &i, params);
		if (expanded == NULL)
			return (NULL);
	}
	return (expanded);
}
