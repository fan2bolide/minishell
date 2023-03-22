#include "execute_cmd_line.h"

static void here_doc_routine(int fd_to_write, char *delimiter);
//return 0 if new_line is not delim, return -1 if new_line is delimiter
static int	append_new_line_if_not_delim(int fd, char **str_to_append, char *delim);

static int append_str(char **str_to_append, char *new_line);

void manage_here_doc(t_cmd cmd)
{
	char	*delimiter;

	if (!cmd.heredoc_mode)
		return;
	delimiter = cmd.heredoc_delim;
//	close(cmd.heredoc_pipe[READ]);
	here_doc_routine(cmd.heredoc_pipe[WRITE], delimiter);
	if (close(cmd.heredoc_pipe[WRITE]) < 0)
	{
		ft_putstr_fd("Failed to close heredoc's pipe\n", 2);
		exit(EXIT_FAILURE); // surement a modifier puisuquon est dans le main thread + partout ou il y a des exiti ici
	}
	return ;
}

static void here_doc_routine(int fd_to_write, char *delimiter) {
	char	*heredoc_buf;
	int		bytes_written;

	heredoc_buf = NULL;
	ft_printf("heredoc> ");
	while (append_new_line_if_not_delim(STDIN_FILENO, &heredoc_buf, delimiter) == 0)
		ft_printf("heredoc> ");
	if (heredoc_buf)
	{
		bytes_written = \
		write(fd_to_write, heredoc_buf, ft_strlen(heredoc_buf));
		if (bytes_written < 0)
			ft_putstr_fd("Error while trying to write in heredoc's pipe\n", 2);
	}
	free(heredoc_buf);
}

static int append_new_line_if_not_delim(int fd, char **str_to_append, char *delim) {
	char	*new_line;

	new_line = get_next_line(fd); // on peut remplacer par un readline (ne pas faire add_history)

	if (ft_strcmp(ft_strtrim(new_line, "\n"), delim) == 0)
	{
		free(new_line);
		return (-1);
	}
	append_str(str_to_append, new_line);
	free(new_line);
	return (0);
}

static int append_str(char **str_to_append, char *new_line)
{
	if (!*str_to_append)
	{
		*str_to_append = ft_strdup(new_line);
		return 1;
	}
	*str_to_append = ft_strjoin(*str_to_append, new_line);
	if (!*str_to_append)
		return (ft_putstr_fd("An error occured (here_doc)(append_line)\n", 2), 0);
	return 1;
}

