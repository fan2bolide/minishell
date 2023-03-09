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
	ft_printf("\n\ncmd.argv[0] : %s\n", cmd.argv[0]);
	ft_printf("cmd.argv[1] : %s\n", cmd.argv[1]);
	ft_printf("cmd.path : %s\n", cmd.path);
	ft_printf("cmd.envp[0] : %s\n", cmd.envp[0]);
	ft_printf("cmd.redirect_out : %s\n", cmd.redirect_out);
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
	dup2(to_read, STDIN_FILENO);
	dup2(to_write, STDOUT_FILENO);
	close(to_read);
	close(to_write);
	execve(cmd.path, cmd.argv, cmd.envp);
	exit(EXIT_FAILURE);
}

