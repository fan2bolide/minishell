/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd(struct s_cmd *cmd)
{
	struct stat	file_status;
	char		*dir;
	int const	success = 0;

	update_exit_code(0);
	if (cmd->argv[1] && cmd->argv[2])
		return (update_exit_code(1), print_error(too_many_args, "cd"));
	dir = cmd->argv[1];
	if (!dir)
		return ;
	if (get_file_status(dir, &file_status) != success)
	{
		ft_putstr_fd("Turboshell: cd: ", 2);
		perror(dir);
		return (update_exit_code(1));
	}
	if (!is_a_dir(&file_status))
		return (update_exit_code(1), error_cd(cmd->argv[1]));
	if (user_has_read_permission(&file_status))
		return (chdir_and_update_pwd(dir, success), (void)0);
	else
	{
		print_error(perm_denied, dir);
		return (update_exit_code(1));
	}
}

void	update_pwd(void)
{
	char	*env_var_oldpwd;
	char	*env_var_newpwd;
	char	*path;

	path = ft_calloc(1024, sizeof(char));
	if (!path)
	{
		print_error(alloc_error, "(update_pwd)");
		exit(EXIT_FAILURE);
	}
	path = getcwd(path, 1024);
	if (!path)
		return (perror("getcwd"));
	env_var_oldpwd = ft_strjoin_secure("OLDPWD=", \
	get_env_var_value("PWD"));
	if (!env_var_oldpwd && get_env_var_value("PWD"))
		print_error(alloc_error, "(update_pwd)");
	env_var_newpwd = ft_strjoin_secure("PWD=", path);
	if (!env_var_newpwd && path)
		print_error(alloc_error, "(update_pwd)");
	insert_or_update_env_var(create_keyval_from_env_var(env_var_oldpwd));
	insert_or_update_env_var(create_keyval_from_env_var(env_var_newpwd));
	free(env_var_oldpwd);
	free(env_var_newpwd);
	return (free(path));
}
