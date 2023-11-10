#include "minishell.h"

void sigint_handler()
{
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

int main() {
	char *command;

	while (1) {
		sig_handling();
		command = readline("$> ");
		if (handle_ctrl_d(command))
			break;
		add_history(command);

		if (checkInput(command) == 0)
			lexer(command);
		free(command);
	}
	return 0;
}
