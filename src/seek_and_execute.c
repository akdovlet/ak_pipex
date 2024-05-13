/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_and_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:52:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/13 12:58:44 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	cmd_exe(t_data *data, int i)
{
	if (ft_strchr(data->cmd[0], '/'))
	{
		if (access(data->cmd[0], X_OK) == -1)
		{
			perror(data->cmd[0]);
			return (false);
		}
		else
		{
			execve(data->cmd[0], data->cmd, data->env);
			return (false);
		}
	}
	else
	{
		if (!find_exec(data->cmd[0], data))
		{
			ft_dprintf(STDERR_FILENO, "%s: command not found\n", data->cmd[0]);
			return (false);
		}
	}
	return (true);
}

int	seek_and_execute(t_data	*data)
{
	int	i;

	i = 2;
	data->ids = malloc(sizeof(pid_t) * (data->ac - 3));
	if (!data->ids)
		return (clear_all(data), exit(EXIT_FAILURE), -1);
	while (i < data->ac - 2)
	{
		data->cmd = ft_multi_split(data->av[i], " \t\n'");
		if (!data->cmd)
			return (1);
		ak_pipe(data, i);
		ft_free(data->cmd);
		i++;
	}
	data->cmd = ft_multi_split(data->av[i], " '");
	if (!data->cmd)
		return (-1);
	ak_pipeout(data, i);
	free(data->ids);
	return (data->exit_code);
}
