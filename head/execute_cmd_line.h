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
# include "minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

void	manage_here_doc(t_cmd cmd);
void	execute_cmd(t_cmd_list **cmd, int to_read, int to_write);
char	*get_path(char *exec_name, t_keyval_list *envp_lst);
void	wait_all_child_proc(int *pids, int childs_counter);
void	close_pipes(int pipes[FOPEN_MAX][2], int i);
void	free_cmd_lst(t_cmd_list **cmd_list);
void	free_cmd(t_cmd *cmd_lst);
void	exit_routine(int pipes[FOPEN_MAX][2], int pids[FOPEN_MAX], int i);
int		open_and_get_fd(char *file, int open_mode, int rights);
t_cmd	*create_new_cmd(void);
void	**ft_keyval_lst_to_str_arr(t_keyval_list *lst);

#endif
