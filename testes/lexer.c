#include "lexer.h"

int lexer(char *cmd)
{
	t_state *state;
	state->quote = 0;
	state->inside_word = 0;
	t_tokens **head;
	t_tokens *node;
	char *buff;
	head = NULL;
	int i = 0;
	int j;
	int	x; 
	while (cmd[i] != '\0')
	{
		if (cmd[i] == SPACE && state->quote == 0 && state->inside_word == 0) // 
		{
			//do nothing
		}
		else if (cmd[i] == SPACE && state->quote == 0 && state->inside_word == 1) // close token
		{
			state->inside_word = 0;
			
		}
		else if (cmd[i] != SPACE && state->quote == 0 && state->inside_word == 0)
		{
			

			state->inside_word == 1;
			j = 0;
			while (cmd[i + j] != SPACE && cmd[i + j] != OPERATOR && aspas)
			{
				j++;
			}
			buff = malloc(sizeof(char)* j + 1);
			x = 0;
			while (x != j)
			{
				buff[x] = cmd[i];
				i++;
				x++;
			}
			buff[x] = '\0';
			node = ft_lstnew(buff);
			ft_lstadd_back(head, node);
			buff = NULL;
		}
		else if (cmd[i] != SPACE && state->quote == 0 && state->inside_word == 1)
		{
			/* code */
		}
		
		

		
		
		
		
		i++;
	}

}





// ls -la
// echo "$PATH" '$PATH'