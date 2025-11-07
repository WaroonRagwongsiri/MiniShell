/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:39:57 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/07 14:52:32 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define PATH_MAX 1024

static int	update_pwd(char ***env_ptr, int update_old_pwd)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;

	if (update_old_pwd)
		new_pwd = ft_strjoin("OLDPWD=", getcwd(cwd, sizeof(cwd)));
	else
		new_pwd = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	if (new_pwd != NULL)
		set_env_var(env_ptr, new_pwd);
	return (1);
}

static void	revise_oldpwd(t_cmd_group *cmd, char *oldpwd)
{
	char	*tmp;

	tmp = ft_strdup("OLDPWD=");
	set_env_var(cmd->env_ptr, ft_strjoin(tmp, oldpwd));
	perror("cd");
	close_builtin_fds(cmd);
}

static char	*expand_home(char *path, char *home)
{
	char	*new_path;

	if (path == NULL)
		return (NULL);
	if (path[0] != '~')
		return (path);
	else
		new_path = ft_strjoin(home, &path[1]);
	return (new_path);
}

static char	*update_path(char *path, char *oldpwd, char *home, int fd)
{
	if (path[0] == '~')
		path = home;
	if (path[0] == '-')
	{
		path = oldpwd;
		ft_putendl_fd(path, fd);
	}
	return (path);
}

int	handle_cd(t_cmd_group *cmd, char *path, char *oldpwd, int fd)
{
	char	*home;

	home = ft_getenv(*(cmd->env_ptr), "HOME");
	if (home == NULL && path[0] == '~')
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	if (ft_strlen(path) == 1)
		path = update_path(path, oldpwd, home, fd);
	path = expand_home(path, home);
	if (update_pwd(cmd->env_ptr, 1) && chdir(path) != 0)
	{
		revise_oldpwd(cmd, oldpwd);
		return (1);
	}
	update_pwd(cmd->env_ptr, 0);
	return (0);
}
