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
#include "minishell.h"


//substituir printf por ft_printf

// void sigint_handler(int signum) {
// 	// Handle Ctrl+C signal (SIGINT) by clearing the current input line
//     (void)signum;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// bool checkQuotes(const char* str) {
//     int len = strlen(str);
//     int doubleQuoteCount = 0;
//     int singleQuoteCount = 0;
//     bool insideDoubleQuotes = false;
// 	int i = 0;
//     while (i < len)
// 	{
//         if (str[i] == '"')
// 		{
//             doubleQuoteCount++;
//             insideDoubleQuotes = !insideDoubleQuotes;
//         } else if (str[i] == '\'' && !insideDoubleQuotes) {
//             singleQuoteCount++;
//         }
// 		i++;
//     }
//     return doubleQuoteCount % 2 == 0 && singleQuoteCount % 2 == 0;
// }


int main() {
	// signal(SIGINT, sigint_handler);
	char *command;

	while (1) {
		command = readline("$> ");
		add_history(command);
		if (!command)
		{
			printf("exit\n");
			exit(1);
		}
		else if (strcmp(command, "\x0C") == 0)
		{
			int i;

			i = 0;
			while(i < 30)
			{
				printf("\n");
				i++;
			}
		}
		// if (!checkQuotes(command)) {
		// 	printf("Error: Missing Quotes\n");
		// }
		// else
        // {
            lexer(command);
        // printf("%s\n", command);
        // }
		free(command);
	}
	return 0;
}
