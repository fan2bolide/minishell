
#include "execute_cmd_line.h"



void **ft_keyval_lst_to_str_arr(t_keyval_list *lst)
{
	size_t arr_size = ft_lstsize((t_list *)lst);
	void	**arr = ft_calloc(arr_size + 1, sizeof(char *)); // todo protect this
	int i = 0;
	while (lst)
	{
		arr[i++] = ft_strjoin_secure(ft_strjoin_secure(lst->content->key,\
		"="), lst->content->value);
		if (!arr[i -1] && lst->content->value)
			ft_putstr_fd("an error occurred (ft_keyval_lst_to_str_arr)\n", 2);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}



/**
 * create a new "keyval"
 *  var must be something like --> abc=value
 * strdup whats before the first equal sign to the key element
 * strdup whats after the first equal sign to the value element
 * @param var
 * @return a new keyval
 */
t_keyval *create_keyval_from_env_var(char *var) {
	t_keyval *res;

	if (!var)
		return NULL; //todo test
	res = create_keyval();
	if (!res)
		return NULL; //todo test
	char *equal = ft_strchr(var, '=');

	if (!equal)
	{
		res->key = ft_strdup(var);
		return res; //todo test
	}

	res->key = ft_strndup(var, equal - var);
	res->value = NULL;
	if (*(equal + 1))
		res->value = ft_strdup(equal +1 );
	return res;
}

void destroy_keyval(void *keyval)
{
	free(((t_keyval *)keyval)->value);
	free(((t_keyval *)keyval)->key);
	free(keyval);
}

t_keyval *create_keyval(void) {
	t_keyval *res = malloc(sizeof(t_keyval));
	if (!res)
		return (ft_putstr_fd("an error occurred (create_keyval..)\n", 2), NULL);
	res->value = NULL;
	res->key = NULL;
	return res;
}
