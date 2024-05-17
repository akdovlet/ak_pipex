/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_and_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:52:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/16 19:55:44 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_exec(char *cmd, t_data *data)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = NULL;
	while (data->path[i])
	{
		full_path = ft_strjoin(data->path[i], cmd);
		if (!full_path)
			return (clear_exit(data, EXIT_FAILURE));
		if (!access(full_path, X_OK))
		{
			execve(full_path, data->cmd, data->env);
			free(full_path);
			perror("pipex");
			clear_exit(data, 127);
		}
		free(full_path);
		i++;
	}
	ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n", data->cmd[0]);
	clear_exit(data, 127);
}

void	cmd_exe(t_data *data)
{
	if (!data->cmd[0])
	{
		ft_dprintf(STDERR_FILENO, "%s: command not found\n", data->cmd[0]);
		clear_exit(data, 127);
	}
	if (ft_strchr(data->cmd[0], '/'))
	{
		if (access(data->cmd[0], X_OK) == -1)
		{
			perror(data->cmd[0]);
			clear_exit(data, 127);
		}
		else
		{
			execve(data->cmd[0], data->cmd, data->env);
			ft_dprintf(STDERR_FILENO, "%s: command not found\n", data->cmd[0]);
			clear_exit(data, 127);
		}
	}
	else
		find_exec(data->cmd[0], data);
}

void	seek_and_execute(t_data	*data)
{
	int	i;

	i = 2;
	data->ids = malloc(sizeof(pid_t) * (data->ac - (3 + data->here_doc)));
	if (!data->ids)
		return (clear_exit(data, EXIT_FAILURE));
	if (data->here_doc)
	{
		i = 3;
		dr_here(data);
	}
	while (i < data->ac - 2)
	{
		data->cmd = ft_multi_split(data->av[i], " '");
		if (!data->cmd)
			return (clear_exit(data, EXIT_FAILURE));
		ak_pipe(data, i);
		ft_free(data->cmd);
		i++;
	}
	data->cmd = ft_multi_split(data->av[i], " '");
	if (!data->cmd)
		return (clear_exit(data, EXIT_FAILURE));
	ak_pipeout(data, i);
}
