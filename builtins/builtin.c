#include "../minishell.h"


extern int	g_exit_status;

void	x_commands(char **cmd, t_data *data)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		b_echo(cmd + 1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		b_cd.c(data, cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		b_pwd();
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		if (cmd[1] == NULL)
			print_exp(data);
		else
			b_export(data, cmd + 1);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
		b_unset(data, cmd + 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		if (cmd[1] == NULL)
			print_env(data);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
		b_exit(cmd, data);
	g_exit_status = 0;
}

int	commands(char **cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	return (0);
}