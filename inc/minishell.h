/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:11:15 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/04 17:25:21 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/stat.h>
# include "../lib/libft/inc/libft.h"
# include "cmds.h"

# ifndef HOSTNAME
#  define HOSTNAME "host"
# endif

extern volatile sig_atomic_t	g_status;

typedef enum s_sig_mode
{
	MAIN,
	CHILD,
	MAIN_CHILD,
	HEREDOC,
	MAIN_HEREDOC
}	t_sig_mode;

// utils_tab.c
char		**copy_tab(char **tab);
void		*free_tab(char **tab);
int			tab_len(char **tab);
char		**append_tab(char **tab, char *str);
char		**split_tokens(char **str);

// reader.c
char		*get_prompt(char ***env_ptr);
char		*reader(char ***env_ptr);

// reader_quotes.c
bool		is_completed_quotes(char **line);

// utils_check.c 
bool		is_whitespace(char c);
bool		is_quotation_mark(char c);
bool		is_special_char(char c);
bool		is_redirect_char(char c);

// utils_quotes.c
void		remove_quotes(char *str);
void		tab_remove_quotes(char **tab);

// tokernizer.c 
char		**tokenizer(char *s);

// debug.c 
void		print_tokens(char *line);
void		print_cmd_group(t_cmd_group	*g);

// expander.c
void		expand_tokens(char **tokens, char ***env_ptr, int *exit_status);

// builtin_cmd1.c
int			builtin_echo(t_cmd_group *cmd);
int			builtin_pwd(t_cmd_group *cmd);
int			builtin_cd(t_cmd_group *cmd);
int			builtin_exit(t_cmd_group *cmd);
int			builtin_env(t_cmd_group *cmd);

// builtin_cmd2.c
void		close_builtin_fds(t_cmd_group *cmd);
int			builtin_export(t_cmd_group *cmd, char ***env_ptr);
int			builtin_unset(t_cmd_group *cmd, char ***env_ptr);

// builtin_cmd3.c
int			builtin_echo_main(t_cmd_group *cmd);
int			builtin_pwd_main(t_cmd_group *cmd);
int			builtin_cd_main(t_cmd_group *cmd);
int			builtin_exit_main(t_cmd_group *cmd);
int			builtin_env_main(t_cmd_group *cmd);

// builtin_cmd4.c
int			builtin_export_main(t_cmd_group *cmd, char ***env_ptr);
int			builtin_unset_main(t_cmd_group *cmd, char ***env_ptr);

// builtin_utils.c
bool		is_valid_identifier(char *arg);
int			find_env_index(char **env, char *arg);
void		print_env(char **env, int fd);
int			append_env(char ***env, char *arg);
int			set_env_var(char ***env, char *arg);
char		*get_env_value(char **env, const char *key);

// exec_buildin.c
int			is_builtin(char *cmd);
int			execute_builtin(t_cmd_group *cmd);
int			execute_builtin_main(t_cmd_group *cmd);

// exec_cmd.c
int			execute_command(t_cmd_group *cmd_lines, char ***env_ptr);

// utils_env.c
char		*ft_getenv(char **env, char *key);
char		*find_cmd(char *cmd, char **env);

// parser_cmd.c
t_cmd_group	*init_cmd_group(char *line, char ***env_ptr, int *exit_status);

// parser_get_info.c
int			next_after_redirect(char **tab, int index);
char		**get_in_filenames(char **tab);
char		**get_out_filenames(char **tab);
char		*get_cmd(char **tab);
char		**get_argv(char **tab);

// parser_check.c
bool		is_heredoc_token(char *token);
bool		is_append_token(char *token);
bool		is_simple_redirect(char *token, char c);

// parser_outfiles.c
void		set_out_files(t_cmd_group *node);

// parser_infiles.c
void		set_in_files(t_cmd_group *node);

// Utils Exit
void		exit_msg(char *msg);
void		exit_cmd(char *cmd, char *err_msg, int exit_status);
void		exit_errno(int exit_status);

// Signal
void		signal_handler(t_sig_mode mode);
void		main_interrupt(int signum);
void		child_interrupt(int signum);
void		child_quit(int signum);
void		heredoc_interrupt(int signum);
void		main_heredoc_interrupt(int signum);

#endif
