/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error_cd(char *file)
{
	ft_putstr_fd("Turboshell: cd: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Not a directory\n", 2);
	update_exit_code(1);
}

void	chdir_and_update_pwd(const char *dir, const int success)
{
	if (chdir(dir) != success)
	{
		perror("chdir() error");
		update_exit_code(1);
	}
	update_pwd();
}

int	user_has_read_permission(struct stat *file_status)
{
	return ((*file_status).st_mode & S_IRUSR);
}

bool	is_a_dir(struct stat *file_status)
{
	return (((*file_status).st_mode & S_IFMT) == S_IFDIR);
}

int	get_file_status(char *file_or_dir, struct stat *result)
{
	return (stat(file_or_dir, result));
}
