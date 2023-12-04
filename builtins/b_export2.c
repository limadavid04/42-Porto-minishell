#include "../minishell.h"

extern int	g_exit_status;

t_exp	*search_exp(char *name, t_status *status)
{
	t_exp	*search;

	search = status->exp;
	while (search != NULL)
	{
		if (ft_strcmp(name, search->v_name) == 0)
			return (search);
		search = search->next;
	}
	return (NULL);
}

int	set_exp(char *name, char *new_value, t_status *status)
{
	t_exp	*new_exp;
	t_exp	*search;

	search = search_exp(name, status);
	if (search)
	{
		if (search->v_value != NULL)
			free(search->v_value);
		search->v_value = ft_strdup(new_value);
		return (0);
	}
	else
	{
		new_exp = new__exp(name, new_value);
		add_exp(&status->exp, new_exp);
		return (0);
	}
	return (-1);
}

char	*get_exp(char *name, t_status *status)
{
	t_exp	*search;

	search = status->exp;
	while (search != NULL)
	{
		if (ft_strcmp(name, search->v_name) == 0)
			return (search->v_value);
		search = search->next;
	}
	return (NULL);
}

void	print_exp(t_status *status)
{
	t_exp	*print;

	print = status->exp;
	while (print)
	{
		if (print->v_value == NULL)
			printf("declare -x %s\n", print->v_name);
		else
			printf("declare -x %s=\"%s\"\n", print->v_name, \
					print->v_value);
		print = print->next;
	}
	g_exit_status = 0;
}