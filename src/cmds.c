/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:09:15 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 13:28:43 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*new_cmd(char **argvs, char **env)
{
	t_cmds	*cmd;

	cmd = ft_safe_calloc(1, sizeof(t_cmds), "");
	if (!cmd)
		return (NULL);
	if (argvs && argvs[0])
		cmd->cmd = argvs[0];
	else
		cmd->cmd = NULL;
	cmd->argv = argvs;
	cmd->env = env;
	cmd->io.fd_in = 0;
	cmd->io.fd_out = 1;
	cmd->io.is_rein = false;
	cmd->io.is_reout = false;
	cmd->io.is_heredoc = false;
	cmd->io.is_append = false;
	cmd->next = NULL;
	return (cmd);
}

int	cmd_len(t_cmds *cmds_lines)
{
	t_cmds	*cur;
	int		len;

	len = 0;
	cur = cmds_lines;
	while (cur)
	{
		cur = cur->next;
		++len;
	}
	return (len);
}
