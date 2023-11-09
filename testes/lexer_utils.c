#include "minishell.h"

int	check_next_char(char *c)
{
	//check for >> or <<
	if((*c) == '>')
	{
		if (*(c + 1) == '>')
			return (1);
	}
	else if ((*c) == '<')
	{
		if (*(c + 1) == '<')
			return (1);
	}
	return (0);
}
int	is_whitespace(char c)
{
	if(c == '\n' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

int is_special_char(char c)
{
	if(c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
int	is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);

}
int is_single_quote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}
int is_double_quote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}
void printLinkedList(t_list* head)
{
    t_list* current = head;

    while (current != NULL) {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
}

void	lst_clear(t_list **lst)
{
	t_list	*temp;
	t_list	*nxt;

	if (lst == NULL)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		nxt = temp->next;
		free(temp->content);
		free(temp);
		temp = nxt;
	}
	*lst = NULL;
}
