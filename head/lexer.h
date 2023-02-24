/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:41:19 by alevra            #+#    #+#             */
/*   Updated: 2023/02/23 16:53:54 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>
# include <stdio.h>
# include "libft.h"
# include "minishell.h"

typedef enum e_type
{
	empty,
	cmd,
	args,
	file,
	operator
}	t_type;

typedef struct s_token
{
	t_type	type;
	char	*content;

}	t_token;

# endif
