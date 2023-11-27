#include "../minishell.h"

int	redirect_input(t_list	*redir)
{
	int	fd;
	t_list	*file;

	file = redir->next;
	fd = open(file->content, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (0);
	}
	dup2(fd, IN);
	close(fd);
	return (1);
}
int	redirect_output(t_list	*redir, int	append)
{
	int	fd;
	t_list	*file;

	file = redir->next;
	if (append == 1)
		fd = open(file->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (0);
	}
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
	//signals need to change exit status
	//make special signals for heredoc that print >
	pid = fork();
	signals_exec();
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
	int		fd;

	delim = heredoc->next->content;
	delim = ft_strjoin(delim, "\n");
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
