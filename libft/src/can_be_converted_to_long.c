#include "libft.h"

//
// Created by Aurelien Levra on 05/04/2023.
//
#define UPPER_STR_LENGTH_LIMIT_FOR_A_LONG 21
#define LOWER_STR_LENGTH_LIMIT_FOR_A_LONG 19

bool can_be_converted_to_long(char *argv1)
{
	const size_t error_attoll1 = 0;
	const size_t error_attoll2 = -1;
	size_t argv1_len;

	argv1_len = ft_strlen(argv1);
	if (argv1_len > UPPER_STR_LENGTH_LIMIT_FOR_A_LONG)
		return false;
	if (argv1_len < LOWER_STR_LENGTH_LIMIT_FOR_A_LONG)
		return true;

	size_t atoll_res = ft_atoll(argv1);
	if (atoll_res == error_attoll1 ||
		atoll_res == error_attoll2)
		return false;
	return true;
}