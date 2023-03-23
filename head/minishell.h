/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <ba...@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:43:37 by bajeanno          #+#    #+#             */
/*   Updated: 2023/03/06 15:00:00 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SPEC_CHAR "<>|&$"
# include "libft.h"
# include <stdio.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_str_list
{
	char			*content;
	struct s_str_list	*next;
}	t_str_list;

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
	env_variable
}	t_type;

typedef struct s_token
{
	t_type	type;
	char	*content;

}	t_token;

typedef struct s_cmd
{
	char	**argv;
	char	*path;
	t_str_list 	**envp_lst_ptr;
	char    *redirect_in;
	char    *redirect_out;
	int 	redirect_out_mode;
	int 	heredoc_mode;
	char	*heredoc_delim;
	int 	heredoc_pipe[2];
	int 	previous_cmd_was_heredoc;
}			t_cmd;

typedef struct s_cmdlist
{
	t_cmd 			*content;
	struct s_cmdlist	*next;
}	t_cmdlist;

static char *pwd;
t_cmdlist * convert_token_lst_into_cmd_lst(t_list *token_lst, t_str_list **envp_list_ptr);
int		token_cmd_line_size(t_list *token_lst);

//debug
t_list	*get_sample_tokens();

int		execute_cmd_line(t_cmdlist *cmd_lst);
void	print_token(t_token *token);
char	*expand_content(char *raw_content, t_str_list **envp);
int		expand_tokens_from_list(t_list *token_list, t_str_list *envp);
t_list	*get_main_token_list(char *command_line);
t_list	*token_parsing(t_list *tokens);
void	destroy_token(void *token);
void	log_token_list(t_list *token_list);
void	exec_builtin(t_cmd *cmd, int to_read, int to_write);
int		is_builtin(char *str);
void	log_cmd_lst(t_list *cmd_list);
void	log_cmd(t_cmd *cmd);
char	*get_env_var_value(char *var_name, t_str_list **envp);
#endif
