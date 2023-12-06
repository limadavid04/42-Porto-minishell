
#include "../minishell.h"

void free_all(t_status *status)
{
	lst_clear(status->token_lst);
	free(status->token_lst);
	free_env(status->env);
	close(status->default_fd[IN]);
	close(status->default_fd[OUT]);
	if (status->old_pipe_in != -1)
		close(status->old_pipe_in);
	rl_clear_history();
	free(status);
}