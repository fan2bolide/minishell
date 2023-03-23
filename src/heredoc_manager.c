#include "execute_cmd_line.h"
#include "builtins.h"

static void here_doc_routine(int fd_to_write, char *delimiter, t_str_list **envp);
//return 0 if new_line is not delim, return -1 if new_line is delimiter
static int append_new_line_if_not_delim(int fd, char **str_to_append, char *delim, t_str_list **envp);
static int append_str(char **str_to_append, char *new_line);
static char *remove_quotes(const char *raw);
static int is_delimiter(char *delim, const char *new_line);

void manage_here_doc(t_cmd cmd)
{

	char	**splits;


	if (!cmd.heredoc_mode)
		return;

	here_doc_routine(cmd.heredoc_pipe[WRITE], cmd.heredoc_delim, cmd.envp_lst_ptr);
	close(cmd.heredoc_pipe[WRITE]);
	return ;
}



static void here_doc_routine(int fd_to_write, char *delimiter, t_str_list **envp)
{
	char	*heredoc_buf;
	int		bytes_written;

	heredoc_buf = NULL;
	ft_printf("heredoc> ");
	while (append_new_line_if_not_delim(STDIN_FILENO, &heredoc_buf, delimiter,envp) == 0)
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

static int append_new_line_if_not_delim(int fd, char **str_to_append, char *delim, t_str_list **envp)
{
	char	*new_line;
	int 	expand_optn;
	expand_optn = 0;
	expand_optn = ft_strchr(delim, '\"') != NULL;
	expand_optn = expand_optn || ft_strchr(delim, '\'') != NULL;



	new_line = get_next_line(fd); // on peut remplacer par un readline (ne pas faire add_history)

	if (is_delimiter(delim, new_line))
	{
		ft_printf("delim found\n"); //debug
		free(new_line); //c'est dans ce cas la que ca segf
		return (-1);
	}
	if (expand_optn)
		append_str(str_to_append, expand_content(new_line, envp));
	else
		append_str(str_to_append, new_line);
	free(new_line);
	return (0);
}

static int is_delimiter(char *delim, const char *new_line)
{
	return ft_strcmp(ft_strtrim(new_line, "\n"), remove_quotes(delim)) == 0;
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

static char *remove_quotes(const char *raw)
{
	int res_size = 0;
	int i = 0;

	ft_printf("removing quotes...\n");
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
	ft_printf("quotes removed !\n");
	return res;
}