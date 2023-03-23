#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	echo(char **argv, int option_n);
void	export2(char *var_to_export, char* var_value, t_list *envp_lst);
void	export(char **argv, t_list **envp_lst_ptr);
int		str_starts_with(char *str, char *keyword);
void	unset(char *var_to_unset, t_list **envp_lst_ptr);
void env(t_list *envp_lst, int to_write);
void	trim_last_folder_if_possible(char *pwd);
void update_pwd(char *dir, t_list *envp_lst);
void cd(t_cmd *cmd);

# endif