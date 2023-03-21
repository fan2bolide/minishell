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
#include "minishell.h"
//'to_read' linked to child ´stdin´ and child ´stdout´ linked to ´to_write´
void	execute_cmd(t_cmd cmd, int to_read, int to_write)
{
	ft_printf("to_read : %d\n", to_read);
	ft_printf("to_write : %d\n", to_write);
	ft_printf("cmd.argv[0] : %s\n", cmd.argv[0]);
	ft_printf("cmd.argv[1] : %s\n", cmd.argv[1]);
	if(is_builtin(cmd.argv[0]) >= 0 || cmd.heredoc_mode)
		exit(EXIT_SUCCESS);
	if (to_read != STDIN_FILENO)
	{
		dup2(to_read, STDIN_FILENO);
		close(to_read);
	}
	if (to_write != STDOUT_FILENO)
	{
		dup2(to_write, STDOUT_FILENO);
		close(to_write);
	}
	execve(cmd.path, cmd.argv,	(char *const*)ft_lst_to_arr(*(cmd.envp_lst_ptr), sizeof(char *)));
	exit(EXIT_FAILURE);
}
