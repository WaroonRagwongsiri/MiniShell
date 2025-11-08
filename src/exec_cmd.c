/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:57:20 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/08 11:01:09 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define IN_ERROR "minishell: syntax error near unexpected token `<'\n"
#define OUT_ERROR "minishell: syntax error near unexpected token `>'\n"

static int	exec_cmd_wraper(t_cmd_group *cmd_lines, int process_num)
{
	if (cmd_lines == 0 || process_num == 0)
		return (0);
	if (process_num > MAX_PROCESS)
	{
		ft_putendl_fd("minishell: too many process", 2);
		return (1);
	}
	if (process_num - 1 > MAX_PIPE)
	{
		ft_putendl_fd("minishell: too many pipes", 2);
		return (1);
	}
	return (exec_cmd(cmd_lines, process_num));
}

static bool	check_redirection_tokens(char **tokens, char c)
{
	int	i;

	if (tokens != NULL)
	{
		i = 0;
		while (tokens[i] != NULL)
		{
			if (tokens[i][0] == c)
			{
				if (c == '<')
					ft_putstr_fd(IN_ERROR, STDERR_FILENO);
				else if (c == '>')
					ft_putstr_fd(OUT_ERROR, STDERR_FILENO);
				return (false);
			}
			i++;
		}
	}
	return (true);
}

static bool	check_parser_filename(t_cmd_group *cmd_lines)
{
	int	process_num;

	process_num = cmd_len(cmd_lines);
	if (cmd_lines == NULL || process_num == 0)
		return (true);
	if (!check_redirection_tokens(cmd_lines->in_filenames, '<'))
		return (false);
	if (!check_redirection_tokens(cmd_lines->out_filenames, '>'))
		return (false);
	return (true);
}

int	execute_command(t_cmd_group *cmd_lines)
{
	int			process_num;

	process_num = cmd_len(cmd_lines);
	if (!check_parser_filename(cmd_lines))
		return (2);
	if (cmd_lines == NULL || process_num == 0 || cmd_lines->cmd == NULL)
		return (0);
	if (process_num == 1
		&& cmd_lines->argv != NULL
		&& cmd_lines->argv[0] != NULL
		&& is_builtin(cmd_lines->argv[0]))
	{
		return (execute_builtin_main(cmd_lines));
	}
	else
	{
		return (exec_cmd_wraper(cmd_lines, process_num));
	}
}
