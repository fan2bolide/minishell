/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:41:19 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 18:41:40 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include <stddef.h>
# include <stdio.h>
# include "libft.h"

typedef enum e_type
{
	error,
	exec_name,
	arg,
	file,
	operator_pipe,
	redirect_in,
	redirect_out,
	redirect_hd,
	redirect_append,
	env_variable
}	t_type;

typedef struct s_token
{
	t_type	type;
	char	*content;

}	t_token;

char	*set_token_content(char *expression);
t_list	*get_token_list(char *command_line);
void	print_token(t_token *token);
void	destroy_token(void *token);
size_t	end_of_quote(char *expression);

# endif
