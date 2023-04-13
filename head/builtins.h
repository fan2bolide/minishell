/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 04:46:15 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/12 04:46:16 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	export(char **argv, int to_write);
void	unset(char *var_to_unset);
void	env(int to_write);
void	echo(char **argv, int option_n);
void	pwd(int fd_to_write);
void	cd(struct s_cmd *cmd);
void	insert_or_update_env_var(t_keyval *keyval_to_insert);
void	shell_exit(t_cmd_list **cmd_list_ptr);
int		user_has_read_permission(struct stat *file_status);
void	chdir_and_update_pwd(const char *dir, const int success);
void	error_cd(char *error_message);
void	update_pwd(void);

#endif
