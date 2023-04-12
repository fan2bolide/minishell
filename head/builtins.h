#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	export(char **argv, int to_write);
void 	unset(char *var_to_unset);
void 	env(int to_write);
void	echo(char **argv, int option_n);
void	 pwd(int fd_to_write);
void	cd(struct s_cmd *cmd);
void	shell_exit(t_cmd_list **cmd_list_ptr);
void	insert_or_update_env_var(t_keyval *keyval_to_insert);

# endif