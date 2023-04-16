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

	if (!g_envp_lst || !g_envp_lst->next)
		return ;
	curr = g_envp_lst->next;
	if (check_export_syntax(argv) <= 0)
	{
		print_error(bad_identifier, "argv[1]");
		update_exit_code(1);
		return ;
	}
	if (!argv[1])
	{
		print_loop(to_write, curr);
		return ;
	}
	keyval_to_export = create_keyval_from_env_var(argv[1]);
	if (!keyval_to_export)
		return (print_error(alloc_error, "(export)"));
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
	int	i;

	i = 0;
	if (argv[1] == NULL)
		return (1);
	if (isalpha(argv[1][i]) || argv[1][i] == '_')
	{
		i++;
		while (argv[1][i] && argv[1][i] != '=' && \
				(ft_isalnum(argv[1][i]) || argv[1][i] == '_'))
			i++;
		if (!argv[1][i] || argv[1][i] == '=')
			return (1);
	}
	return (0);
}
