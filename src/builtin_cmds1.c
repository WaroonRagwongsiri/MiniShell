/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:06:05 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/30 20:23:48 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define PATH_MAX 1024

/*
TODO : handle echo with " "
*/
int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] != NULL && ft_strncmp(args[1], "-n", 2) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*path;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	builtin_cd(char **args, char **env)
{
	char	*path;

	if (args[1] == NULL)
	{
		path = ft_getenv(env, "HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	builtin_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (args[1] != NULL)
		exit_code = ft_atoi(args[1]);
	exit(exit_code);
}

int	builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
