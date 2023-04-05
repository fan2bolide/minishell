#include "libft.h"

//last element of array must be a NULL pointer
void	ft_free_arr(void ** array, void (*del)(void *))
{
	int	i;

	i = 0;
	while(array[i])
		del(array[i++]);
}