
#include "libft.h"

/**
 *
 * @param str
 * @param keyword
 * @return 1 if str starts with keyword, 0 if not
 */
int str_starts_with(char *str, char *keyword)
{
	int res = ft_strncmp(str, keyword, ft_strlen(keyword));
	if (res == 0)
		return (1);
	return (0);
}