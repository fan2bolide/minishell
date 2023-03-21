/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:20:18 by alevra            #+#    #+#             */
/*   Updated: 2023/02/23 14:40:54 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_CMD_LINE_H
# define EXECUTE_CMD_LINE_H

# ifndef READ
#  define READ 0
# endif
# ifndef WRITE
#  define WRITE 1
# endif
# ifndef FILE_1
#  define FILE_1 0
# endif
# ifndef FILE_2
#  define FILE_2 1
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>


typedef struct s_cmd
{
	char	**argv;
	char	*path;
	t_list 	**envp_lst_ptr;
    char    *redirect_in;
    char    *redirect_out;
	int 	redirect_out_mode;
	int 	heredoc_mode;
	char	*heredoc_delim;
	int 	heredoc_pipe[2];
	int 	previous_cmd_was_heredoc;
}			t_cmd;

void manage_here_doc(t_cmd cmd);
void		execute_cmd(t_cmd cmd, int to_read, int to_write);
char		*get_path(char *exec_name, t_list *envp_lst);
void		wait_all_child_proc(int *pids, int childs_counter);
void		close_pipes(int pipes[OPEN_MAX][2],	int i);
void		free_cmd_lst(t_list **cmd_lst);
void		free_cmd(t_cmd *cmd_lst);
void		exit_routine(int pipes[OPEN_MAX][2], int pids[OPEN_MAX], int i);
int			execute_cmd_line(t_list *cmd_lst);
int 		open_and_get_fd(char *file, int open_mode, int rights);
t_cmd		*create_new_cmd(t_list **envp_lst_ptr);
#endif
