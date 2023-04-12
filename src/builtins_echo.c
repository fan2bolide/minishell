/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienlevra <aurelienlevra@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:46:05 by aurelienlev       #+#    #+#             */
/*   Updated: 2023/04/12 01:46:31 by aurelienlev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_echos_option_n(char *argv1);

/* can manage :
 *
 * >echo message
 * >message
 *k
 *>echo -n message
 * message >
 *
 * >echo  message1          message2
 * >message1 message2
 *
 * */
void	echo(char **argv, int to_write)
{
	int	option_n;
	int	i;
	int	success;

	success = 0;
	if (!argv[1])
		return ;
	option_n = is_echos_option_n(argv[1]);
	i = 1 + option_n;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], to_write);
		if (argv[i + 1])
			ft_putstr_fd(" ", to_write);
		i++;
	}
	if (!option_n)
		ft_putstr_fd("\n", to_write);
	update_exit_code(success);
}

static int	is_echos_option_n(char *argv1)
{
	int	i;

	if (!str_starts_with(argv1, "-n"))
		return (0);
	i = 2;
	while (argv1[i] == 'n')
		i++;
	return (argv1[i] == 0);
}
