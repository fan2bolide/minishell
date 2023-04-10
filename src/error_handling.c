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
	char *tmp;

	res = "Turboshell: ";
	if (context == parsing_error)
	{
		update_exit_code(258);
		res = "Turboshell: parsing error near token: ";
		tmp = ft_strjoin(res, token);
		res = ft_strjoin(tmp, "\n");
		free(tmp);
		return(ft_putstr_fd(res, STDERR_FILENO), free(res), (void)0);
	}
	tmp = ft_strjoin(res, token);
	if (context == no_file)
		res = ft_strjoin(tmp, ": no such file or directory\n");
	if (context == unknown_command)
		res = ft_strjoin(tmp, ": command not found\n");
	if (context == perm_denied)
		res = ft_strjoin(tmp, ": Permission denied\n");
	if (context == error_occured)
		res = ft_strjoin(tmp, ": An error occurred\n");
	if (context == alloc_error)
		res = ft_strjoin(tmp, ": allocation error\n");
	if (context == cwd_error)
		res = ft_strjoin(tmp, "error retrieving the current working directory\n");
	if (context == heredoc_pipe_error)
		res = ft_strjoin(tmp, "error while writing in heredoc's pipe\n");
	free(tmp);
	ft_putstr_fd(res, STDERR_FILENO);
	free(res);
}
