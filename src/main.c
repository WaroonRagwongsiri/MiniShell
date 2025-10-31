/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:12:56 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 16:59:25 by waragwon         ###   ########.fr       */
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
	t_cmd_group	*cmd_lines;
	t_cmd_group	*second;
	t_cmd_group	*third;
	int			in_cmd1;
	int			out_cmd1;
	int			in_cmd2;
	int			out_cmd2;
	int			in_cmd3;
	int			out_cmd3;

	cmd_lines = NULL;
	in_cmd1 = 0;
	out_cmd1 = 1;
	in_cmd2 = 0;
	out_cmd2 = 1;
	in_cmd3 = 0;
	out_cmd3 = 1;
	// in_cmd1 = open("in1", O_RDONLY);
	// out_cmd1 = open("out1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// in_cmd2 = open("in2", O_RDONLY);
	// out_cmd2 = open("out2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// in_cmd3 = open("in3", O_RDONLY);
	// out_cmd3 = open("out3", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmd_lines = simple_new_cmd((char *[]) {"/bin/cat", "-e", NULL}, env);
	second = simple_new_cmd((char *[]) {"/bin/cat", "-e", NULL}, env);
	cmd_lines->next = second;
	second->prev = cmd_lines;
	third = simple_new_cmd((char *[]) {"/bin/cat", "-e", NULL}, env);
	second->next = third;
	third->prev = second;
	cmd_lines->in_fd = in_cmd1;
	cmd_lines->out_fd = out_cmd1;
	second->in_fd = in_cmd2;
	second->out_fd = out_cmd2;
	third->in_fd = in_cmd3;
	third->out_fd = out_cmd3;
	printf("Exit Status : %d\n", exec_cmd(cmd_lines));
	ft_safe_calloc(-1, -1, NULL);
	return (EXIT_SUCCESS);
}
