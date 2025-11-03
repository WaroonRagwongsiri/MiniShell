/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:13:29 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/03 13:29:44 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define MAX_PROMPT 1024

bool	is_home_path(char *home, char *path)
{
	int		i;
	bool	check;

	i = 0;
	while (path[i] != '\0' && (home[i] == path[i]))
		i++;
	check = (home[i] == '\0') && (path[i] == '\0' || path[i] == '/');
	return (check);
}

void	prompt_cat(char *prompt, char *user, char *path, char *home)
{
	int	len;

	len = ft_strlcpy(prompt, user, ft_strlen(user) + 1);
	len = ft_strlcat(prompt, "@", len + 2);
	len = ft_strlcat(prompt, HOSTNAME, len + ft_strlen(HOSTNAME) + 1);
	len = ft_strlcat(prompt, ":", len + 2);
	if (home != NULL && is_home_path(home, path))
	{
		len = ft_strlcat(prompt, "~", len + 2);
		path += ft_strlen(home);
	}
	len = ft_strlcat(prompt, path, len + ft_strlen(path) + 1);
	ft_strlcat(prompt, " $ ", len + 4);
}

char	*get_prompt(char ***env_ptr)
{
	char	*path;
	char	*home;
	char	*user;
	char	*prompt;
	char	buffer[MAX_PROMPT];

	prompt = NULL;
	path = ft_getenv(*env_ptr, "PWD");
	if (path == NULL)
		path = getcwd(buffer, MAX_PROMPT);
	home = ft_getenv(*env_ptr, "HOME");
	if (home == NULL)
		home = "";
	user = ft_getenv(*env_ptr, "USER");
	if (user == NULL)
		user = "user";
	prompt = ft_safe_calloc(1, MAX_PROMPT , "");
	if (prompt == NULL)
		return (NULL);
	prompt_cat(prompt, user, path, home);
	return (prompt);
}

char	*reader(char ***env_ptr)
{
	char	*prompt;
	char	*line;

	prompt = get_prompt(env_ptr);
	if (prompt == NULL)
		return (NULL);
	line = readline(prompt);
	if (line == NULL)
		return (NULL);
	if (!is_completed_quotes(&line) && line == NULL)
	{
		line = ft_strdup("");
		if (line == NULL)
			return (NULL);
	}
	if (line != NULL && ft_strlen(line) > 0)
		add_history(line);
	return (line);
}
