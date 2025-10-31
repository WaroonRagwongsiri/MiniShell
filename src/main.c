/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:12:56 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 21:24:05 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define DEBUG_MODE 0

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
	t_cmd_group	*cmd_lines;
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
		cmd_lines = init_cmd_group(line, mini_env);
		if (DEBUG_MODE)
			print_cmd_group(cmd_lines);
		exit_status = exec_cmd(cmd_lines);
		clean_cmd_group(cmd_lines);
		free(line);
	}
	return (EXIT_SUCCESS);
}
