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

void		manage_here_doc(t_cmd cmd);
void		execute_cmd(t_cmd_list **cmd, int fds[2]);
char		*get_path(char *exec_name, t_keyval_list *envp_lst);
void		wait_all_child_proc(int *pids, int childs_counter);
void		close_pipes(int pipes[OPEN_MAX][2], int i);
void		free_cmd_lst(t_cmd_list **cmd_list);
void		free_cmd(t_cmd *cmd_lst);
void		exit_routine(int pipes[OPEN_MAX][2], int pids[OPEN_MAX], int i);
int			open_and_get_fd(char *file, int open_mode, int rights);
t_cmd		*create_new_cmd(void);
void		**ft_keyval_lst_to_str_arr(t_keyval_list *lst);
void		\
case_current_token_type_is_exec_name(t_token_list *token_lst_cursor, \
t_cmd *cmd);
void		get_fds(t_cmd_list *cmd_lst, \
int pipes[10240][2], int i, int fds[2]);
void		close_fds(int fds[2], t_cmd_list *cmd_lst);
void		check_path(const t_cmd_list *cmd_lst);
int			check_if_single_builtin(t_cmd_list **cmd_lst, const int *fds);
int			create_and_check_pipes(int pipes[10240][2], int i, \
t_cmd_list *cmd_lst);
t_cmd_list	*destroy_first_cmd_lst(t_cmd_list *cmd_lst);
int			is_last_cmd(t_cmd_list *cmd);
void		dup2_fds(int to_read, int to_write);
void		heredoc_only_hook(t_cmd *cmd);
void		builtin_hook(t_cmd_list **cmd_list_ptr, const int *fds, \
t_cmd *cmd, const int to_write);
void		check_fds(t_cmd_list **cmd_list_ptr, const int *fds, \
const int to_read, const int to_write);

#endif
