/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_content.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 06:13:38 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/12 06:13:39 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_CONTENT_H
# define EXPAND_CONTENT_H

# include "minishell.h"

typedef enum e_expand_token_type
{
	double_quote,
	quote,
	word,
}	t_token_type;

typedef struct s_expansion
{
	t_token_type	type;
	char			*content;
}	t_expansion;

void	destroy_expand_token(void *token);
void	remove_quotes(t_list *token_list);
int		replace_with_value(void *expansion_token);
char	*join_contents(t_list *token_list);

#endif
