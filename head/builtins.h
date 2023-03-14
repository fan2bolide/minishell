#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		is_builtin(char *str);
void	echo(char *msg, int option_n);
char	*get_env_var(char *env_var, char **envp);
void	export2(char *var_to_export, char* var_value, char **envp);
void	export(char *arg, char **envp);
int		str_starts_with(char *str, char *keyword);
void	unset(char *var_to_unset, char **envp);
void	pwd(char *pwd);
void	env(char **envp);
void	trim_last_folder_if_possible(char *pwd);
void	update_pwd(char *dir, char **envp, char* pwd);
void	cd(char *dir, char** envp, char *pwd);

# endif