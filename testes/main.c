#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void sigint_handler(int signum) {
    // Handle Ctrl+C signal (SIGINT) by clearing the current input line
    printf("\n");
	rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int verify_input(char *cmd)
{
    int i = 0;
    int one = 0;
    int two = 0;
    int pos = 0;

    while (cmd[i])
    {
        if (cmd[i] == "\"")
        {
            two = i;
        }
        else if 
        i++;
        if (one % 2 != 0 && two % 2 != 0)
            printf("Error: Missing Quote");
    }
}

int main() {
    // Set custom signal handler for Ctrl+C (SIGINT)
    signal(SIGINT, sigint_handler);

    // Set the initial prompt without "^C"
    char *command;

    while (1) {
        command = readline("$> ");
		add_history(command);
        verify_input(command)
        if (command == NULL) {
            // Handle end of input (e.g., Ctrl+D)
            printf("exit\n");
            exit(0);
        }

        if (strcmp(command, "\x0C") == 0) { // Check for Ctrl+L (ASCII code 12)
            // Clear the screen by printing multiple newline characters
            int i;
            for (i = 0; i < 30; ++i) {
                printf("\n");
            }
        }
        free(command);
    }

    return 0;
}
