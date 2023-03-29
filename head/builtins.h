#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void export(char **argv, int to_write);
int		str_starts_with(char *str, char *keyword);
void unset(char *var_to_unset);
void env(int to_write);

void	echo(char **argv, int option_n);
void pwd(int fd_to_write);

void cd(struct s_cmd *cmd);

# endif