#include "../minishell.h"

int	redirect_input(t_list	*redir)
{
	int	fd;
	char *new_filename;

	new_filename = process_tokens(redir->next->content, 1);
	// printf("NEW filename = %s\n", new_filename);
	fd = open(new_filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(errno, strerror(errno), new_filename);
		free(new_filename);
		return (0);
	}
	free(new_filename);
	dup2(fd, IN);
	close(fd);
	return (1);
}
int	redirect_output(t_list	*redir, int	append)
{
	int	fd;
	char *new_filename;

	new_filename = process_tokens(redir->next->content, 1);
	// printf("NEW filename = %s\n", new_filename);
	if (append == 1)
		fd = open(new_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(errno, strerror(errno), new_filename);
		free(new_filename);
		return (0);
	}
	free(new_filename);
	dup2(fd, OUT);
	close(fd);
	return (1);
}
void create_heredoc_subprocess(char *delim, t_status *status)
{
	int pid;
	char buff[4095];
	int	out;
	int	fd;
	int	exit_code;
	pid = fork();
	if (pid == 0)
	{
		fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(status->default_fd[OUT], "> ", 2);
		out = read(status->default_fd[IN], buff, 4095);
		//fd 1 might not point to stdin;
		while (out > 0)
		{
			buff[out] = '\0';
			if (!ft_strncmp(buff, delim, out))
				break ;
			ft_putstr_fd(buff, fd);
			write(status->default_fd[OUT], "> ", 2);
			out = read(status->default_fd[IN], buff, 4095);
		}
		close(fd);
		if(status->old_pipe_in != -1)
			close(status->old_pipe_in);
		free(delim);
		lst_clear(status->token_lst);
		free(status->token_lst);
		close(status->default_fd[IN]);
		close(status->default_fd[OUT]);
		free(status);
		exit(0);
	}
	waitpid(pid, &exit_code,0);
	// g_exit_status = exit;
}

int	handle_heredoc(t_list	*heredoc, t_status *status)
{
	char	*delim;
	char	*temp;
	int		fd;

	temp = process_tokens(heredoc->next->content, 0);
	delim = ft_strjoin(temp, "\n");
	free(temp);
	// printf("new_delim = %s\n", delim);
	create_heredoc_subprocess(delim, status);
	free(delim);
	fd = open(".heredoc", O_RDONLY, 0644);
	dup2(fd, IN);
	close(fd);
	unlink(".heredoc");
	return (1);
}
int	redirect_handler(t_list *cmd_start, t_list *pipe_tkn, t_status *status)
{
	t_list	*cur;

	cur = cmd_start;
	while (cur != pipe_tkn)
	{
		if (!ft_strncmp(cur->content, ">", ft_strlen(cur->content)))
		{
			if (!redirect_output(cur, 0))
				return (0);
		}
		else if (!ft_strncmp(cur->content, ">>", ft_strlen(cur->content)))
		{
			if (!redirect_output(cur, 1))
				return (0);
		}
		else if (!ft_strncmp(cur->content, "<", ft_strlen(cur->content)))
		{
			if (!redirect_input(cur))
				return (0);
		}
		else if (!ft_strncmp(cur->content, "<<", ft_strlen(cur->content)))
		{
			if (!handle_heredoc(cur, status))
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}