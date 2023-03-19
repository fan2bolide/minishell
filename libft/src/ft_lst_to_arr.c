#include "libft.h"

void	**ft_lst_to_arr(t_list *lst, size_t size_of_arr_elemnt)
{
	size_t arr_size = ft_lstsize(lst);
	void	**arr = ft_calloc(arr_size + 1, size_of_arr_elemnt); // todo protect this
	int i = 0;

	while (lst)
	{
		arr[i++] = lst->content;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}