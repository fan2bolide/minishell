#include "libft.h"

//
// Created by Aurelien Levra on 04/04/2023.
//

bool str_contains_digits_only(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (!ft_isdigit((int)str[i]))
			return (false);
		i++;
	}
	return (true);
}