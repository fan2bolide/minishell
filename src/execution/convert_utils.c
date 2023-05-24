/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:59:35 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

void	try_to_create_file(t_cmd *cmd, int open_mode, char *file)
{
	int	fd;

	if (open_mode == O_TRUNC && !cmd->error)
	{
		fd = open(file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (fd > 0)
			close(fd);
		else
		{
			update_exit_code(1);
			cmd->error = true;
			print_error(perm_denied, file);
		}
	}
}
