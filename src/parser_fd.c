/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:18:38 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 21:12:23 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_last_entry(char **tab)
{
	int	i;

	if (tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
		i++;
	if (i == 0)
		return (NULL);
	return (tab[i - 1]);
}

static int	last_out_is_append(char **tokens, char *filename)
{
	int	i;
	int	append;

	if (tokens == NULL || filename == NULL)
		return (0);
	i = 0;
	append = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strncmp(tokens[i], ">>", 3) == 0 && tokens[i + 1] != NULL
			&& ft_strncmp(tokens[i + 1], filename,
				ft_strlen(tokens[i + 1]) + 1) == 0)
			append = 1;
		else if (ft_strncmp(tokens[i], ">", 2) == 0 && tokens[i + 1] != NULL
			&& ft_strncmp(tokens[i + 1], filename,
				ft_strlen(tokens[i + 1]) + 1) == 0)
			append = 0;
		i++;
	}
	return (append);
}

static int	open_input_fd(char **filenames)
{
	char	*last_in;
	int		fd;

	fd = STDIN_FILENO;
	last_in = get_last_entry(filenames);
	if (last_in != NULL)
	{
		fd = open(last_in, O_RDONLY);
		if (fd == -1)
			exit_msg("Open Input File");
	}
	return (fd);
}

static int	open_output_fd(t_cmd_group *node)
{
	char	*last_out;
	int		flags;
	int		fd;

	fd = STDOUT_FILENO;
	last_out = get_last_entry(node->out_filenames);
	if (last_out != NULL)
	{
		flags = O_WRONLY | O_CREAT;
		if (last_out_is_append(node->cmd_tokens, last_out))
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(last_out, flags, 0644);
		if (fd == -1)
			exit_msg("Open Output File");
	}
	return (fd);
}

void	set_cmd_group_fd(t_cmd_group *node)
{
	if (node == NULL)
		return ;
	node->in_fd = open_input_fd(node->in_filenames);
	node->out_fd = open_output_fd(node);
}
