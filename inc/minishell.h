/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:11:15 by pioncha2          #+#    #+#             */
/*   Updated: 2025/10/31 15:22:20 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../lib/libft/inc/libft.h"
# include "cmds.h"

// utils_tab.c
char		**copy_tab(char **tab);
void		*free_tab(char **tab);
int			tab_len(char **tab);

// reader.c
char		*get_prompt(char **env);
char		*reader(char **env);

// utils_check.c 
bool		is_whitespace(char c);
bool		is_quotation_mark(char c);
bool		is_special_char(char c);
bool		is_redirect_char(char c);

// tokernizer.c 
char		**tokenizer(char *s);

// debug.c 
void		print_tokens(char *line);

// exec_cmd.c
int			ft_execve(char *cmd_path, char **cmd, char **env);
int			execute_command(char **cmd, char **env);

// exec_redirect.c
int			handle_output_redirect(char *filename, int append);
int			handle_input_redirect(char *filename);
int			process_redirect(char **cmd);

// builtin_cmd1.c
int			builtin_echo(char **args);
int			builtin_pwd(void);
int			builtin_cd(char **args, char **env);
int			builtin_exit(char **args);
int			builtin_env(char **env);

// builtin_cmd2.c
int			builtin_export(char **args, char ***env);
int			builtin_unset(char **args, char ***env);

// exec_buildin.c
int			is_builtin(char *cmd);
int			execute_builtin(char **args, char **env);

// utils_env.c
char		*ft_getenv(char **env, char *key);

#endif