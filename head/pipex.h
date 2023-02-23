/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:20:18 by alevra            #+#    #+#             */
/*   Updated: 2023/02/23 14:14:45 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

typedef struct s_to_exec
{
1	char	**cmd;
 	char	*path;
	char	**envp;
}			t_to_exec;



void		manage_here_doc(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i,
				int fd_file_1);
int			append_new_line_if_not_delim(int fd, char **str_to_append,
				char *delim);
void		here_doc_routine(int pipes[OPEN_MAX][2], int i, char *delimiter);
void		execute_cmd(t_to_exec to_exec, int to_read, int to_write);
char		*get_path(char *cmd, char **envp);
void		wait_all_child_proc(int *pids, int childs_counter);
void		close_pipes_and_file_fd(int pipes[OPEN_MAX][2], int files[2],
				int i);
void		free_cmd_tab(t_to_exec **cmds);
void		free_cmd_tab2(t_to_exec *cmds);
t_to_exec	*parser(char **splits, char **envp);
void		exit_routine(int pipes[OPEN_MAX][2], int files[2],
				int pids[OPEN_MAX], int i);
int			execute_all_cmds(t_to_exec *cmds, int files[2]);
#endif



typedef struct t_parsing_msh
{
	ce que tu veux

}			t_parsing_msh;
