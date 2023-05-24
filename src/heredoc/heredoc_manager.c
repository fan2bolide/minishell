/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <aurelienlevra@student.42           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:50:44 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:54:03 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execute_cmd_line.h"

static void	here_doc_routine(int fd_to_write, char *delimiter);
//return 0 if new_line is not delim, return -1 if new_line is delimiter
static int	append_new_line_if_not_delim(char **str_to_append, char *delim);
static int	is_delimiter(char *delim, const char *next_line);

void	manage_here_doc(t_cmd *cmd)
{
	int	pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		setup_signals(sig_handler_heredoc_mode);
		if (!cmd->heredoc_mode || !cmd->heredoc_delim)
			return (close(cmd->heredoc_pipe[WRITE]), (void)0);
		here_doc_routine(cmd->heredoc_pipe[WRITE], cmd->heredoc_delim);
		setup_signals(sig_handler_execution_mode);
		exit(EXIT_SUCCESS);
	}
	close(cmd->heredoc_pipe[WRITE]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == EXIT_FAILURE)
			cmd->abort_cmd_line = true;
	}
}

static void	here_doc_routine(int fd_to_write, char *delimiter)
{
	char	*heredoc_buf;
	int		bytes_written;

	heredoc_buf = NULL;
	while (append_new_line_if_not_delim(&heredoc_buf, \
	delimiter) == 0)
		;
	if (heredoc_buf)
	{
		bytes_written = \
			write(fd_to_write, heredoc_buf, ft_strlen(heredoc_buf));
		if (bytes_written < 0)
			print_error(heredoc_pipe_error, "");
	}
	free(heredoc_buf);
}

static int	append_new_line_if_not_delim(char **str_to_append, char *delim)
{
	char	*next_line;
	char	*tmp;
	int		expand_optn;

	expand_optn = (ft_strchr(delim, '\"') == NULL && \
	ft_strchr(delim, '\'') == NULL);
	next_line = readline("heredoc >");
	if (!next_line)
		return (append_str(str_to_append, "\n"), -1);
	if (is_delimiter(delim, next_line))
		return (free(next_line), append_str(str_to_append, "\n"), -1);
	if (expand_optn)
	{
		tmp = expand_content(next_line);
		if (!tmp)
			return (-1);
		next_line = tmp;
	}
	if (*str_to_append)
		append_str(str_to_append, "\n");
	append_str(str_to_append, next_line);
	return (free(next_line), 0);
}

static int	is_delimiter(char *delim, const char *next_line)
{
	char	*tmp;
	int		res;
	char	*delim_without_quotes;

	tmp = NULL;
	tmp = ft_strdup((char *)next_line);
	if (!tmp && printf("An error occurred \n"))
		return (0);
	delim_without_quotes = remove_quotes_heredoc(delim);
	if (!delim_without_quotes)
	{
		print_error(alloc_error, "(heredoc_manager)");
		res = 1;
	}
	else
		res = (ft_strcmp(tmp, delim_without_quotes) == 0);
	free(delim_without_quotes);
	free(tmp);
	return (res);
}
