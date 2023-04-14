/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:39:11 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/20 01:03:51 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif
# ifndef EOF
#  define EOF (-1)
# endif

char	*ft_strfusion(char const *buf, int *size, char *line, int buf_size);
char	*ft_realloc_str(char *str, int new_size);

#endif