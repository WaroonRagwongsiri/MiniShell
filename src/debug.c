/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:04 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 20:57:24 by pioncha2         ###   ########.fr       */
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

static void	print_str_tab(char *label, char **tab)
{
	int			i;

	printf("%s", label);
	if (tab == NULL)
	{
		printf("(null)\n");
		return ;
	}
	i = 0;
	while (tab[i] != NULL)
		printf("[%s] ", tab[i++]);
	printf("\n");
}

void	print_cmd_group(t_cmd_group *g)
{
	t_cmd_group	*curr;
	int			i;

	curr = g;
	i = 0;
	printf("---\n");
	while (curr != NULL)
	{
		printf("== cmds[%d] ==\n", i);
		printf("cmds_str : %s\n", curr->cmds_str);
		print_str_tab("cmd_token: ", curr->cmd_tokens);
		print_str_tab("in_filenames: ", curr->in_filenames);
		print_str_tab("out_filenames: ", curr->out_filenames);
		printf("cmds : %s\n", curr->cmd);
		print_str_tab("argv: ", curr->argv);
		printf("operator: %d\n", curr->operator);
		printf("---\n");
		curr = curr->next;
		i++;
	}
}
