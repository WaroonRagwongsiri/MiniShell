/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:12:56 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 15:43:56 by waragwon         ###   ########.fr       */
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

	cmd_lines = NULL;
	cmd_lines = simple_new_cmd((char *[]) {"/bin/ls", NULL}, env);
	cmd_lines->next = simple_new_cmd((char *[]) {"/bin/cat", NULL}, env);
	cmd_lines->next = simple_new_cmd((char *[]) {"/bin/cat", NULL}, env);
	printf("Exit Status : %d\n", exec_cmd(cmd_lines));
	ft_safe_calloc(-1, -1, NULL);
	return (EXIT_SUCCESS);
}
