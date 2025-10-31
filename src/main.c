/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:12:56 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/01 00:02:16 by waroonwork@      ###   ########.fr       */
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

// int	main(int ac, char **av, char **env)
// {
// 	t_cmd_group	*cmd_lines;
// 	t_cmd_group	*second;
// 	t_cmd_group	*third;
// 	int			in_cmd1;
// 	int			out_cmd1;
// 	int			in_cmd2;
// 	int			out_cmd2;
// 	int			in_cmd3;
// 	int			out_cmd3;

// 	cmd_lines = NULL;
// 	cmd_lines = simple_new_cmd((char *[]) {"sleep", "20", NULL}, env);
// 	second = simple_new_cmd((char *[]) {"sleep", "10", NULL}, env);
// 	cmd_lines->next = second;
// 	second->prev = cmd_lines;
// 	third = simple_new_cmd((char *[]) {"sleep", "5", NULL}, env);
// 	second->next = third;
// 	third->prev = second;
// 	cmd_lines->is_heredoc = true;
// 	second->is_heredoc = true;
// 	third->is_heredoc = true;
// 	printf("Exit Status : %d\n", exec_cmd(cmd_lines));
// 	ft_safe_calloc(-1, -1, NULL);
// 	return (EXIT_SUCCESS);
// }
