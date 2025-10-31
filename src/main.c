/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/10/31 14:42:15 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

static void	exit_after_reader(char **mini_env)
{
	clear_history();
	free_tab(mini_env);
	printf("\nexit\n");
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	char		**mini_env;
	char		**tokens;
	int			exit_status;

	if (ac != 1 || av[0] == NULL)
		return (EXIT_FAILURE);
	mini_env = copy_tab(env);
	if (mini_env == NULL)
		return (EXIT_FAILURE);
	while (true)
	{
		line = reader(mini_env);
		if (line == NULL)
			exit_after_reader(mini_env);
		tokens = tokenizer(line);
		if (tokens != NULL)
		{
			exit_status = execute_command(tokens, mini_env);
			printf("Exit status: %d\n", exit_status);
			free_tab(tokens);
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
