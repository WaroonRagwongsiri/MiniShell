/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:12:56 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 14:02:39 by waragwon         ###   ########.fr       */
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
	static t_shell	shell;
	t_cmds	*cmd_lines;

	cmd_lines = new_cmd((char *[]) {"/bin/ls", NULL}, env);
	cmd_lines->next = new_cmd((char *[]) {"/bin/cat", NULL}, env);
	cmd_lines->next->next = new_cmd((char *[]) {"/bin/cat", NULL}, env);
	cmd_lines = NULL;
	shell.env = env;
	shell.cmd_lines = cmd_lines;
	shell.process_num = cmd_len(cmd_lines);
	ft_safe_calloc(-1, -1, NULL);
	return (exec_cmd(&shell));
}
