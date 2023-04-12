/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	check_numeric_argument(char *argv1);

void	shell_exit(t_cmd_list **cmd_list_ptr)
{
	int			exit_code_modulo;
	const char	*exit_code;
	t_cmd		*cmd;
	char		*argv1;

	cmd = (*cmd_list_ptr)->content;
	argv1 = cmd->argv[1];
	ft_printf("exit\n");
	exit_code = envp_lst->content->value;
	exit_code_modulo = ft_atoi(exit_code) % 256;
	ft_lstclear((t_list **)&envp_lst, &destroy_keyval);
	if (!argv1)
	{
		ft_lstclear((t_list **)cmd_list_ptr, (void (*)(void *)) & destroy_cmd);
		exit(exit_code_modulo);
	}
	if (check_numeric_argument(argv1) == false)
	{
		print_error(numeric_argument_required, ft_strjoin_secure("exit: ", argv1));
		exit(255);
	}
	exit_code_modulo = ft_atoll(argv1) % 256;
	ft_lstclear((t_list **)cmd_list_ptr, (void (*)(void *)) & destroy_cmd);
	exit(exit_code_modulo);
}

static bool	check_numeric_argument(char *argv1)
{
	if (!can_be_converted_to_long(argv1))
		return (false);
	if (argv1[0] == '-')
		argv1++;
	if (!str_contains_digits_only(argv1))
		return (false);
	return (true);
}
