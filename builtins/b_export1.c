#include "../minishell.h"

void	free_exp2(t_exp *tmp)
{
	if (!tmp)
		return ;
	free(tmp->v_name);
	free(tmp->v_value);
	free(tmp);
}

void	free_exp(t_exp *exp)
{
	t_exp	*tmp;

	while (exp)
	{
		tmp = exp;
		exp = exp->next;
		free_exp2(tmp);
	}
}

t_exp	*new__exp(char *v_name, char *v_value)
{
	t_exp	*new_exp;

	new_exp = malloc(sizeof(t_exp));
	if (!new_exp)
		return (0);
	new_exp->v_name = ft_strdup(v_name);
	new_exp->v_value = ft_strdup(v_value);
	new_exp->next = NULL;
	return (new_exp);
}

void	add_exp(t_exp **exp, t_exp *new)
{
	t_exp	*curr;

	if (*exp == NULL || ft_strcmp((*exp)->v_name, new->v_name) >= 0)
	{
		new->next = *exp;
		*exp = new;
	}
	else
	{
		curr = *exp;
		while (curr->next != NULL && ft_strcmp(curr->next->v_name, \
				new->v_name) < 0)
			curr = curr->next;
		new->next = curr->next;
		curr->next = new;
	}
}

void	exp_create(t_status *status, char **exp)
{
	size_t	len;
	int		i;
	char	*v_name;
	char	*v_value;
	t_exp	*new_exp;

	i = 0;
	while (exp[i])
	{
		if (ft_strchr(exp[i], '='))
		{
			len = ft_strchr(exp[i], '=') - exp[i];
			v_name = malloc(len + 1);
			ft_memcpy(v_name, exp[i], len);
			v_name[len] = '\0';
			v_value = ft_strdup(ft_strchr(exp[i], '=') + 1);
			new_exp = new__exp(v_name, v_value);
			add_exp(&status->exp, new_exp);
		}
		free(v_name);
		free(v_value);
		i++;
	}
}