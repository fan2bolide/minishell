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

static char	*get_error_msg_from_context(enum e_error_context context, \
										char *generic_error_msg)
{
	char	*res;

	if (context == no_file)
		res = ft_strjoin(generic_error_msg, \
		": no such file or directory\n");
	if (context == unknown_command)
		res = ft_strjoin(generic_error_msg, ": command not found\n");
	if (context == perm_denied)
		res = ft_strjoin(generic_error_msg, ": Permission denied\n");
	if (context == error_occured)
		res = ft_strjoin(generic_error_msg, ": An error occurred\n");
	if (context == alloc_error)
		res = ft_strjoin(generic_error_msg, ": allocation error\n");
	if (context == cwd_error)
		res = ft_strjoin(generic_error_msg, \
		"error retrieving working directory\n");
	if (context == heredoc_pipe_error)
		res = ft_strjoin(generic_error_msg, \
		"error while writing in heredoc's pipe\n");
	if (context == numeric_argument_required)
		res = ft_strjoin(generic_error_msg, \
		": numeric argument required\n");
	if (context == bad_identifier)
		res = ft_strjoin(generic_error_msg, \
		": not a valid identifier\n");
	if (context == too_many_args)
		res = ft_strjoin(generic_error_msg, \
		": too many arguments\n");
	return (res);
}

void	print_error(enum e_error_context context, char *token)
{
	char	*res;
	char	*tmp;

	res = "Turboshell: ";
	if (context == parsing_error)
	{
		update_exit_code(258);
		res = "Turboshell: parsing error near token: ";
		tmp = ft_strjoin(res, token);
		res = ft_strjoin(tmp, "\n");
		free(tmp);
		return (ft_putstr_fd(res, STDERR_FILENO), free(res), (void)0);
	}
	tmp = ft_strjoin(res, token);
	res = get_error_msg_from_context(context, tmp);
	free(tmp);
	ft_putstr_fd(res, STDERR_FILENO);
	free(res);
}
