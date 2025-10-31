/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:04 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/30 18:17:04 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_tokens(char *line)
{
	char	**tokens;
	int		i;

	tokens = tokenizer(line);
	i = 0;
	printf("\ntokens : ");
	while (tokens[i] != NULL)
	{
		printf("[%s] ", tokens[i]);
		i++;
	}
	printf("\n\n");
}
