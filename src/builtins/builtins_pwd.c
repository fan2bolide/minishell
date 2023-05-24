/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd(int fd_to_write)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		print_error(cwd_error, "");
	else
		ft_putstr_fd(cwd, fd_to_write);
	ft_putstr_fd("\n", fd_to_write);
	free(cwd);
}
