#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void sigint_handler() {
	// Handle Ctrl+C signal (SIGINT) by clearing the current input line
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	handle_ctrl_d(char *cmd)
{
	if (!cmd)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

void sig_handling()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

bool checkQuotes(const char* str) {
    int len = strlen(str);
    int doubleQuoteCount = 0;
    int singleQuoteCount = 0;
    bool insideDoubleQuotes = false;
	int i = 0;
    while (i < len) 
	{
        if (str[i] == '"') 
		{
            doubleQuoteCount++;
            insideDoubleQuotes = !insideDoubleQuotes;
        } else if (str[i] == '\'' && !insideDoubleQuotes) {
            singleQuoteCount++;
        }
		i++;
    }
    return doubleQuoteCount % 2 == 0 && singleQuoteCount % 2 == 0;
}


int main() {
	char *command;

	while (1) {
		sig_handling();
		command = readline("$> ");
		if (handle_ctrl_d(command))
			break;
		add_history(command);

		if (!checkQuotes(command)) {
			printf("Error: Missing Quotes\n");
		}
		else
			printf("%s\n", command);
		free(command);
	}
	return 0;
}
