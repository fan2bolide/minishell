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
	error,
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

char	*get_token_content(char *expression);
t_list	*get_token_list(char *command_line);
void	print_token(t_token *token);
void	destroy_token_list(t_token **token_list);

# endif
