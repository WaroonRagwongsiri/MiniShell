/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:12:56 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 18:39:45 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define DEBUG_MODE 0

static void	exit_after_reader(void)
{
	rl_clear_history();
	ft_safe_calloc(-1, -1, NULL);
	printf("\nexit\n");
	exit(EXIT_SUCCESS);
}

static char	**init_environment(char **env)
{
	char	**mini_env;

	mini_env = copy_tab(env);
	if (mini_env == NULL)
		exit(EXIT_FAILURE);
	return (mini_env);
}

static void	run_shell(char ***env_ptr)
{
	char		*line;
	t_cmd_group	*cmd_lines;
	int			exit_status;

	exit_status = 0;
	while (true)
	{
		signal_handler(MAIN);
		line = reader(env_ptr);
		if (line == NULL)
			exit_after_reader();
		cmd_lines = init_cmd_group(line, env_ptr, &exit_status);
		if (DEBUG_MODE)
			print_cmd_group(cmd_lines);
		exit_status = execute_command(cmd_lines, env_ptr);
	}
}

int	main(int ac, char **av, char **env)
{
	char	**mini_env;

	if (ac != 1 || av[0] == NULL)
		return (EXIT_FAILURE);
	mini_env = init_environment(env);
	run_shell(&mini_env);
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
// 	cmd_lines = simple_new_cmd((char *[]) {"cat", "-e", NULL}, env);
// 	second = simple_new_cmd((char *[]) {"cat", "-e", NULL}, env);
// 	cmd_lines->next = second;
// 	second->prev = cmd_lines;
// 	third = simple_new_cmd((char *[]) {"cat", "-e", NULL}, env);
// 	second->next = third;
// 	third->prev = second;
// 	cmd_lines->in_files = new_infile("in1", false, NULL);
// 	second->in_files = new_infile(NULL, true, "EOF");
// 	third->in_files = new_infile(NULL, true, "EOF");
// 	third->out_files = new_outfile("out3", true);
// 	printf("Exit Status : %d\n", exec_cmd(cmd_lines));
// 	ft_safe_calloc(-1, -1, NULL);
// 	return (EXIT_SUCCESS);
// }
