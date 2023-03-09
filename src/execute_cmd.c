/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:25:43 by alevra            #+#    #+#             */
/*   Updated: 2023/02/08 22:12:59 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

//'to_read' linked to child ´stdin´ and child ´stdout´ linked to ´to_write´
void	execute_cmd(t_cmd cmd, int to_read, int to_write)
{
	dup2(to_read, STDIN_FILENO);
	dup2(to_write, STDOUT_FILENO);
	if (cmd.redirect_in)
	{
		close(to_read);
		to_read = open_and_get_fd(cmd.redirect_in, O_RDONLY, 0);
	}
	if (cmd.redirect_out)
	{
		close(to_write);
		to_write = open_and_get_fd(cmd.redirect_out, O_WRONLY | cmd.redirect_out_mode | O_CREAT, 0644);
	}

	if (execve(cmd.path, cmd.argv, cmd.envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

