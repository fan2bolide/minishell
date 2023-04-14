/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		print_loop(int to_write, t_keyval_list *curr);
static int		check_export_syntax(char **argv);

void	export(char **argv, int to_write)
{
	t_keyval_list	*curr;
	t_keyval		*keyval_to_export;

	if (!g_envp_lst)
		return ;
	curr = g_envp_lst;
	if (check_export_syntax(argv) <= 0)
		return (printf("Bad syntax\n"), (void)(0));
	if (!argv[1])
	{
		print_loop(to_write, curr);
		return ;
	}
	keyval_to_export = create_keyval_from_env_var(argv[1]);
	if (!keyval_to_export)
		return (print_error(error_occured, "export"));
	insert_or_update_env_var(keyval_to_export);
}

static void	print_loop(int to_write, t_keyval_list *curr)
{
	while (curr)
	{
		ft_putstr_fd("declare -x ", to_write);
		ft_putstr_fd(curr->content->key, to_write);
		if (curr->content->value)
		{
			ft_putstr_fd("=\"", to_write);
			ft_putstr_fd(curr->content->value, to_write);
			ft_putstr_fd("\"", to_write);
		}
		ft_putstr_fd("\n", to_write);
		curr = curr->next;
	}
}

static int	check_export_syntax(char **argv)
{
	if (argv[1] == NULL)
		return (1);
	if (isalpha(argv[1][0]) || argv[1][0] == '_')
		return (1);
	return (0);
}
