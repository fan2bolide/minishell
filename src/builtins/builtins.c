/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <aurelienlevra@student.42           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:46:39 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:47:25 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			check_export_syntax(char **argv);
int			is_echos_option_n(char *argv1);
void		free_keyval(void *uncasted_keyval);
void		insert_env_var(t_keyval *keyval_to_insert);
void		update_env_var(t_keyval *keyval_to_update);
bool		env_var_exist(t_keyval *keyval_to_check);
void		shell_exit(t_cmd_list **cmd);
bool		check_numeric_argument(char *argv1);

void	exec_builtin(t_cmd_list **cmd_list_ptr, int to_write)
{
	int		type;
	t_cmd	*cmd;

	if (to_write < 0)
		return ;
	cmd = (*cmd_list_ptr)->content;
	type = is_builtin(cmd->argv[0]);
	if (type == 0 && !cmd->error)
		echo(cmd->argv, to_write);
	else if (type == 1 && !cmd->error)
		cd(cmd);
	else if (type == 2 && !cmd->error)
		pwd(to_write);
	else if (type == 3 && !cmd->error)
		export(cmd->argv, to_write);
	else if (type == 4 && !cmd->error)
		unset(cmd->argv[1]);
	else if (type == 5 && !cmd->error)
		env(to_write);
	else if (type == 6 && !cmd->error)
		shell_exit(cmd_list_ptr);
	if (to_write > STDERR_FILENO)
		close(to_write);
}

// returns -1 if str is not a builtins
// returns [0...6] if str is builtins
int	is_builtin(char *str)
{
	const char	*builtins[] = \
	{"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			i;

	if (!str)
		return (-1);
	i = 0;
	while (i < 7)
		if (ft_strequ(str, builtins[i++]))
			return (i - 1);
	return (-1);
}
