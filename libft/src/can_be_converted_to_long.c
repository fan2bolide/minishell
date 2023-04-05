# include "libft.h"

//
// Created by Aurelien Levra on 05/04/2023.
//


bool can_be_converted_to_long(char *argv1)
{
	const size_t error_attoll1 = 0;
	const size_t error_attoll2 = -1;
	const int upper_str_length_limit_for_a_long = 21;
	const int lower_str_length_limit_for_a_long = 19;


	size_t argv1_len = ft_strlen(argv1);
	if (argv1_len > upper_str_length_limit_for_a_long)
		return false;
	if (argv1_len < lower_str_length_limit_for_a_long)
		return true;

	size_t atoll_res = ft_atoll(argv1);
	if (atoll_res == error_attoll1 ||
		atoll_res == error_attoll2)
		return false;
	return true;
}