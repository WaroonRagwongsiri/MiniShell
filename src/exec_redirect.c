/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:16:49 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 11:02:36 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_output_redirect(char *filename, int append)
{
	int	fd;
	int	flags;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_input_redirect(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	process_redirect(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL && !is_redirect_char(cmd[i][0]))
		i++;
	if (cmd[i] == NULL)
		return (0);
	if (ft_strncmp(cmd[i], "<", 2) == 0)
	{
		if (handle_input_redirect(cmd[i + 1]) == -1)
			return (-1);
	}
	else if (ft_strncmp(cmd[i], ">", 2) == 0)
	{
		if (handle_output_redirect(cmd[i + 1], 0) == -1)
			return (-1);
	}
	else if (ft_strncmp(cmd[i], ">>", 3) == 0)
	{
		if (handle_output_redirect(cmd[i + 1], 1) == -1)
			return (-1);
	}
	else
		return (0);
	return (1);
}
