/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:15:06 by bajeanno          #+#    #+#             */
/*   Updated: 2023/03/23 08:06:58 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_content.h"

void	destroy_expand_token(void *token)
{
	t_expansion	*to_destroy;

	to_destroy = token;
	free(to_destroy->content);
	free(to_destroy);
}
