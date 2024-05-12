/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_and_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:52:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/12 19:10:50 by akdovlet         ###   ########.fr       */
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
	int	exit_code;

	exit_code = 0;
	i = 2;
	while (i < data->ac - 2)
	{
		data->cmd = ft_split(data->av[i], ' ');
		if (!data->cmd)
			return (1);
		ak_pipe(data, i);
		ft_free(data->cmd);
		i++;
	}
	data->cmd = ft_split(data->av[i], ' ');
	if (!data->cmd)
		return (-1);
	exit_code = ak_pipeout(data);
	ft_free(data->cmd);
	ft_free(data->path);
	return (exit_code);
}
