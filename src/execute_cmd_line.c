/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 18:41:04 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static int get_fd_to_read(int pipes[OPEN_MAX][2], int i, t_cmd cmd);
static int	get_fd_to_write(int	pipes[OPEN_MAX][2], int i, t_cmd_list *cmd_lst);
static int	is_last_cmd(t_cmd_list *cmd);
void check_path(const t_cmd_list *cmd_lst);
int create_and_check_pipes(int pipes[OPEN_MAX][2], int i);
void get_fds(t_cmd_list *cmd_lst, int pipes[OPEN_MAX][2], int i, int *fd_to_read, int *fd_to_write);

void close_fds(int fd_to_read, int fd_to_write);

bool is_single_builtin_cmd(t_cmd_list *cmd_lst);

static void error_depending_on_file_or_dir(char *cmd_with_issue);

void check_if_is_dir(char *path);

int	execute_cmd_line(t_cmd_list *cmd_lst)
{
	int	pipes[OPEN_MAX][2];
	int	pids[OPEN_MAX];
	int fd_to_read;
	int fd_to_write;
	int	i;

	i = 0;
	ft_memset(pipes, 0 , sizeof(int) * OPEN_MAX * 2);
	while (cmd_lst)
	{
		check_path(cmd_lst);
		if (!is_last_cmd(cmd_lst))
			if (!create_and_check_pipes(pipes, i))
				return (0);
		get_fds(cmd_lst, pipes, i, &fd_to_read, &fd_to_write);
		if (is_single_builtin_cmd(cmd_lst))
			return(exec_builtin(&cmd_lst, fd_to_write), 1);
		pids[i] = fork();
		if (pids[i] < 0)
			return (ft_printf("Failed to fork\n"), 0);
		if (pids[i] == 0)
			execute_cmd(&cmd_lst,\
			fd_to_read,\
			fd_to_write);
		close_fds(fd_to_read, fd_to_write);
		if ((cmd_lst->content)->heredoc_mode)
			close((cmd_lst->content)->heredoc_pipe[READ]);
		cmd_lst = cmd_lst->next;
		i++;
	}
	return (exit_routine(pipes, pids, i), free_cmd_lst(&cmd_lst), 1);
}

bool is_single_builtin_cmd(t_cmd_list *cmd_lst) {
	if (!cmd_lst->next)
		if (cmd_lst->content->argv)
			if (is_builtin(cmd_lst->content->argv[0]) >= 0)
				return (true);
	return (false);
}

void close_fds(int fd_to_read, int fd_to_write) {
	if (fd_to_read != STDIN_FILENO)
		close(fd_to_read);
	if (fd_to_write != STDOUT_FILENO)
		close(fd_to_write);
}

void get_fds(t_cmd_list *cmd_lst, int pipes[OPEN_MAX][2], int i, int *fd_to_read, int *fd_to_write) {
	(*fd_to_read) = get_fd_to_read(pipes, i, *(cmd_lst->content));
	(*fd_to_write) = get_fd_to_write(pipes, i, cmd_lst);
}

static int get_fd_to_read(int pipes[OPEN_MAX][2], int i, t_cmd cmd)
{
	int res;

	if (cmd.redirect_in)
		res = open_and_get_fd(cmd.redirect_in, O_RDONLY, 0);
	else if (cmd.heredoc_mode)
	{
		if (i != 0)
			close (pipes[i - 1][READ]);
		res = cmd.heredoc_pipe[READ];
	}
	else if (i == 0)
		res = STDIN_FILENO;
	else
		res = (pipes[i - 1][READ]);
	return res;
}

static int	get_fd_to_write(int	pipes[OPEN_MAX][2], int i, t_cmd_list *cmd_lst)
{
	int res;
	t_cmd *cmd;

	cmd = cmd_lst->content;
	if (cmd->redirect_out)
		res = open_and_get_fd(cmd->redirect_out, O_WRONLY | cmd->redirect_out_mode | O_CREAT, 0644);
	else if (is_last_cmd(cmd_lst))
		res = STDOUT_FILENO;
	else
		res = (pipes[i][WRITE]);
	return (res);
}

static int	is_last_cmd(t_cmd_list *cmd)
{
	return (cmd->next == NULL);
}

void check_path(const t_cmd_list *cmd_lst) {
	
	int is_an_issue;
	char *cmd_with_issue;
	is_an_issue =0;
	if (!cmd_lst->content->path)
		if (cmd_lst->content->argv && cmd_lst->content->argv[0])
			if (*cmd_lst->content->argv[0])
				is_an_issue = 1;

	if (!is_an_issue)
		return (check_if_is_dir(cmd_lst->content->path));
	cmd_with_issue = (cmd_lst->content)->argv[0];
	if (str_starts_with(cmd_with_issue, "./") || str_starts_with( cmd_with_issue, "/"))
		error_depending_on_file_or_dir(cmd_with_issue);
	else
		ft_printf("Turboshell: command not found: %s\n", (cmd_lst->content)->argv[0]);


}

void check_if_is_dir(char *path) {
	struct stat file_status;
	int const success = 0;

	if (!path)
		return ;
	if (str_starts_with(path, "./"))
		path +=2 ;
	if (get_file_status(path, &file_status) != success)
		return ;
	if (is_a_dir(&file_status)) {
		ft_putstr_fd(path,2);
		ft_putstr_fd(": is a directory\n", 2);
	}
}

static void error_depending_on_file_or_dir(char *cmd_with_issue) {

	struct stat file_status;
	int const success = 0;

	if (!cmd_with_issue)
		return ;
	ft_putstr_fd(cmd_with_issue,2);
	if (get_file_status(cmd_with_issue, &file_status) != success)
		ft_putstr_fd(" : No such file or directory \n",2);
	else
		ft_putstr_fd(" : is a file or a directory \n",2);

}

int create_and_check_pipes(int pipes[OPEN_MAX][2], int i) {
	if (pipe(pipes[i]) < 0)
		return (ft_printf("Failed to create pipes\n"), 0);
	return (1);
}

