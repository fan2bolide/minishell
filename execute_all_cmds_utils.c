/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all_cmds_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/02/16 18:37:49 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//return 0 if new_line is not delim, return -1 if new_line is delimiter
int	append_new_line_if_not_delim(int fd, char **str_to_append, char *delim)
{
	char	*new_line;
	char	*str_to_append_tmp;

	new_line = get_next_line(fd);
	if (ft_strncmp(new_line, delim, ft_max(ft_strlen(new_line),
				ft_strlen(delim))) == 10)
	{
		free(new_line);
		return (-1);
	}
	str_to_append_tmp = ft_strjoin(*str_to_append, new_line);
	if (!str_to_append_tmp)
		ft_printf("An error occured (here_doc)(append_line)\n");
	free(*str_to_append);
	free(new_line);
	*str_to_append = str_to_append_tmp;
	return (0);
}

void	here_doc_routine(int pipes[OPEN_MAX][2], int i, char *delimiter)
{
	char	*to_write_in_pipe;
	int		bytes_written;

	to_write_in_pipe = NULL;
	ft_printf("> ");
	while (append_new_line_if_not_delim(0, &to_write_in_pipe, delimiter) == 0)
		ft_printf("> ");
	if (to_write_in_pipe)
	{
		bytes_written = \
		write(pipes[i][WRITE], to_write_in_pipe, ft_strlen(to_write_in_pipe));
		if (bytes_written < 0)
		{
			ft_printf("Error while trying to write in pipe %d\n", i);
			ft_printf("%s\n", strerror(errno));
		}
	}
	free(to_write_in_pipe);
}

void	manage_here_doc(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i,
		int fd_file_1)
{
	char	*delimiter;

	delimiter = to_exec.cmd[1];
	here_doc_routine(pipes, i, delimiter);
	close(fd_file_1);
	if (close(pipes[i][WRITE]) < 0)
	{
		ft_printf("Failed to close pipe %d\n", i);
		exit(EXIT_FAILURE);
	}
	exit(1);
}
