#include "execute_cmd_line.h"
#include "builtins.h"

static void here_doc_routine(int fd_to_write, char *delimiter);
//return 0 if new_line is not delim, return -1 if new_line is delimiter
static int append_new_line_if_not_delim(int fd, char **str_to_append, char *delim);
static int append_str(char **str_to_append, char *next_line);
static char *remove_quotes(const char *raw);
static int is_delimiter(char *delim, const char *next_line);
void manage_here_doc(t_cmd cmd)
{
	if (!cmd.heredoc_mode)
		return;
	here_doc_routine(cmd.heredoc_pipe[WRITE], cmd.heredoc_delim);
	close(cmd.heredoc_pipe[WRITE]);
}

static void here_doc_routine(int fd_to_write, char *delimiter)
{
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

static int append_new_line_if_not_delim(int fd, char **str_to_append, char *delim)
{
	char	*next_line;
	int 	expand_optn;

	expand_optn = 0;
	expand_optn = ft_strchr(delim, '\"') == NULL && ft_strchr(delim, '\'') == NULL;

	next_line = get_next_line(fd); // on peut remplacer par un readline (ne pas faire add_history)
	if (!next_line)
		return (ft_printf("\n"), -1);
	if (is_delimiter(delim, next_line))
	{
		free(next_line);
		return (-1);
	}
	if (expand_optn)
	{
		if (next_line[0])
			next_line[ft_strlen(next_line) - 1]= 0;
		next_line = expand_content(next_line);
		if (next_line)
			append_str(str_to_append, next_line);
		append_str(str_to_append, "\n");
	}
	else
		append_str(str_to_append, next_line);
	free(next_line);
	return (0);
}

static int is_delimiter(char *delim, const char *next_line)
{
	char *tmp;

	tmp = NULL;
	if (!new_line)
		return 0;
	tmp = ft_strdup((char *)next_line);
	if (!tmp && ft_printf("An error occurred \n"))
		return 0;
	if (tmp[0])
		tmp[ft_strlen(tmp) - 1]= 0;
	int res = ft_strcmp(tmp, remove_quotes(delim)) == 0;
	free(tmp);
	return (res);
}

static int append_str(char **str_to_append, char *next_line)
{
	if (!*str_to_append)
	{
		*str_to_append = ft_strdup(next_line);
		return 1;
	}
	*str_to_append = ft_strjoin(*str_to_append, next_line);
	if (!*str_to_append)
		return (ft_putstr_fd("An error occurred (here_doc)(append_line)\n", 2), 0);
	return 1;
}

static char *remove_quotes(const char *raw)
{
	int res_size = 0;
	int i = 0;

	if (!raw)
		return NULL;
	while (raw[i])
	{
		res_size += ((raw[i] != '\'') && (raw[i] != '\"'));
		i++;
	}
	char * res;
	res = malloc(res_size * sizeof(char));
	if (!res)
		return NULL;
	i = 0;
	int j = 0;
	while (raw[i])
	{
		if ((raw[i] != '\'') && (raw[i] != '\"'))
		{
			res[j] = raw[i];
			j++;
		}
		i++;
	}
	return res;
}
