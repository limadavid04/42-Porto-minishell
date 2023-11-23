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
int	redirect_handler(t_list *cmd_start, t_list *pipe_tkn)
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
		cur = cur->next;
	}
	return (1);
}
