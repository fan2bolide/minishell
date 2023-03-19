#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	exec_builtin(t_cmd *cmd, int to_read, int to_write);
int		is_builtin(char *str);
void	echo(char **argv, int option_n);
char	*get_env_var(char *env_var, char **envp);
void	export2(char *var_to_export, char* var_value, t_list *envp_lst);
void	export(char **argv, t_list **envp_lst_ptr);
int		str_starts_with(char *str, char *keyword);
void	unset(char *var_to_unset, t_list **envp_lst_ptr);
void env(t_list *envp_lst, int to_write);
void	trim_last_folder_if_possible(char *pwd);
void update_pwd(char *dir, t_list *envp_lst);
void cd(t_cmd *cmd);

# endif