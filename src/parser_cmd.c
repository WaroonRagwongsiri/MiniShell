/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:03:53 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 20:06:32 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_in_filenames(char **tab)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], "<", 1) == 0)
		{
			if (tab[i + 1] != NULL)
				res = append_tab(res, tab[i + 1]);
			i += 2;
		}
		else
			i++;
	}
	return (res);
}

char	**get_out_filenames(char **tab)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], ">", 1) == 0 || ft_strncmp(tab[i], ">>", 2) == 0)
		{
			if (tab[i + 1] != NULL)
				res = append_tab(res, tab[i + 1]);
			i += 2;
		}
		else
			i++;
	}
	return (res);
}

char	*get_cmd(char **tab)
{
	return (ft_strdup(tab[0]));
}
char	**get_argv(char **tab, char *cmd)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], ">", 1) == 0 || ft_strncmp(tab[i], "<", 1) == 0)
		{
			if (tab[i + 1] != NULL)
				i += 2;
			else
				i++;
		}
		else
		{
 			if (ft_strncmp(tab[i], cmd, ft_strlen(tab[i])) != 0)
				res = append_tab(res, tab[i]);
			i++;
		}
	}
	return (res);
}

t_cmd_group	*init_cmd_group(char *line, char **env)
{
	char		**tab;
	t_cmd_group	*cmd_group;
	int			i;

	tab = ft_split(line, '|');
	if (tab_len(tab) < 1)
		return (NULL);
	cmd_group = malloc(sizeof(t_cmd_group) * (tab_len(tab) + 1));
	i = 0;
	while (tab[i] != NULL)
	{
		cmd_group[i].cmds_str = ft_strdup(tab[i]);
		cmd_group[i].cmd_tokens = tokenizer(tab[i]);
		cmd_group[i].in_filenames = get_in_filenames(cmd_group[i].cmd_tokens);
		cmd_group[i].out_filenames = get_out_filenames(cmd_group[i].cmd_tokens);
		cmd_group[i].cmd = get_cmd(cmd_group[i].cmd_tokens);
		cmd_group[i].argv = get_argv(cmd_group[i].cmd_tokens, cmd_group[i].cmd);
		cmd_group[i].env = env;
		if (tab[i + 1] != NULL)
		{
			cmd_group[i].operator = PIPE;
			cmd_group[i].next = &cmd_group[i + 1];
		}
		else
		{
			cmd_group[i].operator = NONE;
			cmd_group[i].next = NULL;
		}
		if (i == 0)
			cmd_group[i].prev = NULL;
		else
			cmd_group[i].prev = &cmd_group[i - 1];
		
		i++;
	}
	cmd_group[i].next = NULL;
	free_tab(tab);
	return (cmd_group);
}