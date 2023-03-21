/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all_cmds_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/02/23 15:25:29 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

//return 0 if new_line is not delim, return -1 if new_line is delimiter
int	append_new_line_if_not_delim(int fd, char **str_to_append, char *delim)
{
	char	*new_line;
	char	*str_to_append_tmp;

	new_line = get_next_line(fd); // on peut remplacer par un readline (ne pas faire add_history)
	if (ft_strcmp(new_line, delim) == '\n')
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

void here_doc_routine(int fd_to_write, char *delimiter)
{
	char	*heredoc_buf;
	int		bytes_written;

	heredoc_buf = NULL;
	ft_printf("heredoc> ");
	while (append_new_line_if_not_delim(0, &heredoc_buf, delimiter) == 0)
		ft_printf("heredoc> ");
	if (heredoc_buf)
	{
		bytes_written = \
		write(fd_to_write, heredoc_buf, ft_strlen(heredoc_buf));
		if (bytes_written < 0)
		{
			ft_printf("Error while trying to write in heredoc's pipe\n");
			ft_printf("%s\n", strerror(errno));
		}
	}
	free(heredoc_buf);
}

void manage_here_doc(t_cmd cmd)
{
	char	*delimiter;
	int 	pipe_heredoc[2];

	delimiter = cmd.heredoc_delim;
	pipe(pipe_heredoc);
	dup2(fd_to_write, pipe_heredoc[READ]);
	close(fd_to_write);
	here_doc_routine(pipe_heredoc[WRITE], delimiter);
	if (close(pipe_heredoc[WRITE]) < 0)
	{
		ft_printf("Failed to close heredoc's pipe\n");
		exit(EXIT_FAILURE);
	}
	exit(1);
}
