/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:55:57 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static void	error_depending_on_file_or_dir(char *cmd_with_issue);
static void	check_if_is_dir(char *path);

void	check_path(const t_cmd_list *cmd_lst)
{
	int		is_an_issue;
	char	*cmd_with_issue;

	is_an_issue = 0;
	if (!cmd_lst->content->path)
		if (cmd_lst->content->argv && cmd_lst->content->argv[0])
			if (*cmd_lst->content->argv[0])
				is_an_issue = 1;
	if (!is_an_issue)
		return (check_if_is_dir(cmd_lst->content->path));
	cmd_with_issue = (cmd_lst->content)->argv[0];
	if (str_starts_with(cmd_with_issue, "./") \
	|| str_starts_with(cmd_with_issue, "/"))
		error_depending_on_file_or_dir(cmd_with_issue);
	else
		printf("Turboshell: command not found: %s\n", \
		(cmd_lst->content)->argv[0]);
}

void	check_if_is_dir(char *path)
{
	struct stat	file_status;
	int const	success = 0;

	if (!path)
		return ;
	if (str_starts_with(path, "./"))
		path += 2;
	if (get_file_status(path, &file_status) != success)
		return ;
	if (is_a_dir(&file_status))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
}

static void	error_depending_on_file_or_dir(char *cmd_with_issue)
{
	struct stat	file_status;
	int const	success = 0;

	if (!cmd_with_issue)
		return ;
	ft_putstr_fd(cmd_with_issue, 2);
	if (get_file_status(cmd_with_issue, &file_status) != success)
		ft_putstr_fd(" : No such file or directory \n", 2);
	else
		ft_putstr_fd(" : is a file or a directory \n", 2);
}
