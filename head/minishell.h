/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:43:37 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/12 04:46:50 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SPEC_CHAR "<>|&$"
# define ANSI_RED "\001\x1b[31m\002"
# define ANSI_RESET "\001\x1b[0m\002"
# define ANSI_BLUE "\001\x1b[34m\002"
# include "libft.h"
# include <stdio.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

enum						e_error_context
{
	no_file,
	unknown_command,
	parsing_error,
	perm_denied,
	alloc_error,
	cwd_error,
	heredoc_pipe_error,
	numeric_argument_required,
	bad_identifier,
	too_many_args,
	error_occured
};

typedef struct s_str_list
{
	char					*content;
	struct s_str_list		*next;
}							t_str_list;

typedef struct s_keyval
{
	char					*key;
	char					*value;
}							t_keyval;

typedef struct s_keyval_list
{
	t_keyval				*content;
	struct s_keyval_list	*next;
}							t_keyval_list;

typedef enum e_type
{
	error,
	exec_name,
	arg,
	file,
	operator_pipe,
	redirect_in,
	redirect_out_trunc,
	redirect_hd,
	redirect_out_append,
}							t_type;

typedef struct s_token
{
	t_type					type;
	char					*content;

}							t_token;

typedef struct s_token_list
{
	t_token					*content;
	struct s_token_list		*next;
}							t_token_list;

typedef struct s_cmd
{
	char					**argv;
	char					*path;
	char					*redirect_in;
	char					*redirect_out;
	int						redirect_out_mode;
	int						heredoc_mode;
	char					*heredoc_delim;
	int						heredoc_pipe[2];
	bool					error;
}							t_cmd;

typedef struct s_cmd_list
{
	t_cmd					*content;
	struct s_cmd_list		*next;
}							t_cmd_list;

extern t_keyval_list		*g_envp_lst;

t_cmd_list					*convert_token_lst_into_cmd_lst(t_token_list \
																	*token_lst);
size_t						token_cmd_line_size(t_token_list *token_lst);
int							execute_cmd_line(t_cmd_list *cmd_lst);
size_t						end_of_quote(char *expression);
char						*expand_content(char *raw_content);
int							expand_tokens_from_list(t_token_list *token_list);
t_token_list				*get_main_token_list(char *command_line);
t_token_list				*token_parsing(t_token_list *tokens);
void						destroy_token(void *token);
void						exec_builtin(t_cmd_list **cmd, int to_write);
int							is_builtin(char *str);
char						*get_env_var_value(char *var_name);
t_keyval_list				*convert_str_arr_into_new_keyval_list(char **array);
t_keyval					*create_keyval_from_env_var(char *var);
t_keyval					*create_keyval(void);
void						update_exit_code(int exit_code);
int							get_exit_code(void);
bool						set_exit_code(void);
void						print_error(enum e_error_context context,
								char *token);
bool						is_a_dir(struct stat *file_status);
int							get_file_status(char *file_or_dir,
								struct stat *result);
void						destroy_keyval(void *keyval);
void						destroy_cmd(t_cmd *cmd);
int							setup_signals(void (sig_handler)(int));
void						sig_handler_interactive_mode(int sig);
void						sig_handler_execution_mode(int sig);
void						shell_exit(t_cmd_list **cmd_list_ptr);
bool						check_terminal(void);
void						dup_envp(char **envp);
void						update_env_var(t_keyval *keyval_to_update);
int							backup_termios(struct termios *termios_to_backup);
int							restore_termios(struct termios *termios_to_restore);
int							disable_ctrl_backslash(void);

#endif
