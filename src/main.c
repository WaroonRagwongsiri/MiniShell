/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:12:56 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/08 10:44:08 by pioncha2         ###   ########.fr       */
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

static int	update_shlvl(char **mini_env)
{
	char	*shlvl_str;
	int		shlvl_value;
	char	*new_shlvl;
	char	*env_var;
	int		result;

	shlvl_str = get_env_value(mini_env, "SHLVL");
	if (shlvl_str == NULL)
		shlvl_value = 0;
	else
		shlvl_value = ft_atoi(shlvl_str) + 1;
	if (shlvl_value < 0)
		shlvl_value = 0;
	new_shlvl = ft_itoa(shlvl_value);
	if (!new_shlvl)
		return (-1);
	env_var = ft_strjoin("SHLVL=", new_shlvl);
	if (!env_var)
		return (-1);
	result = set_env_var(&mini_env, env_var);
	return (result);
}

static char	**init_environment(char **env)
{
	char	**mini_env;

	mini_env = copy_tab(env);
	if (mini_env == NULL)
		exit(EXIT_FAILURE);
	if (update_shlvl(mini_env) != 0)
		exit_errno(EXIT_FAILURE);
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
		if (!is_valid_tokens(line))
		{
			exit_status = get_exit_stats(2);
			continue ;
		}
		if (g_status == SIGINT)
			exit_status = get_exit_stats(130);
		cmd_lines = init_cmd_group(line, env_ptr, &exit_status);
		if (DEBUG_MODE)
			print_debug(cmd_lines, line);
		exit_status = get_exit_stats(execute_command(cmd_lines));
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
