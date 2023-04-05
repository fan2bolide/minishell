/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:55:14 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/04 01:07:43 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(enum e_error_context context, char *token)
{
	char *res;

	res = "Turboshell: ";
	if (context == parsing_error)
	{
		res = ft_strjoin(res, "parsing error near token: ");
		res = ft_strjoin(res, token);
		return(ft_putstr_fd(res, STDERR_FILENO), free(res), (void)0);
	}
	res = ft_strjoin(res, token);
	if (context == no_file)
		res = ft_strjoin(res, ": no such file or directory\n");
	if (context == unknown_command)
		res = ft_strjoin(res, ": command not found\n");
	if (context == perm_denied)
		res = ft_strjoin(res, ": Permission denied\n");
	if (context == error_occured)
		res = ft_strjoin(res, ": An error occurred\n");
	if (context == alloc_error)
		res = ft_strjoin(res, ": allocation error\n");
	if (context == cwd_error)
		res = ft_strjoin(res, "error retrieving the current working directory\n");
	if (context == heredoc_pipe_error)
		res = ft_strjoin(res, "error while writing in heredoc's pipe\n");
	ft_putstr_fd(res, STDERR_FILENO);
	free(res);
}
