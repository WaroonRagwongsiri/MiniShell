/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:04 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 20:16:35 by pioncha2         ###   ########.fr       */
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

void	print_cmd_group(t_cmd_group	*g)
{
	t_cmd_group	*curr;
	int			i;

	curr = g;
	printf("---\n");
	while (curr != NULL)
	{
		printf("cmds_str : %s\n", curr->cmds_str);
		
		printf("cmd_token: ");
		if (curr->cmd_tokens != NULL)
		{
			i = 0;
			while (curr->cmd_tokens[i] != NULL)
			{
				printf("[%s] ", curr->cmd_tokens[i]);
				i++;
			}
		}
		printf("\n");
		
		printf("in_filenames: ");
		if (curr->in_filenames != NULL)
		{
			i = 0;
			while (curr->in_filenames[i] != NULL)
			{
				printf("[%s] ", curr->in_filenames[i]);
				i++;
			}
		}
		printf("\n");

		printf("out_filenames: ");
		if (curr->out_filenames != NULL)
		{
			i = 0;
			while (curr->out_filenames[i] != NULL)
			{
				printf("[%s] ", curr->out_filenames[i]);
				i++;
			}
		}
		printf("\n");

		printf("cmds : %s\n", curr->cmd);

		printf("argv: ");
		if (curr->argv != NULL)
		{
			i = 0;
			while (curr->argv[i] != NULL)
			{
				printf("[%s] ", curr->argv[i]);
				i++;
			}
		}
		printf("\n");

		printf("operator: %d\n", curr->operator);
		printf("---\n");
		
		curr = curr->next;
	}
}
