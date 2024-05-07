/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_and_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:52:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/07 20:05:17 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	cmd_exe(t_data *data, int i)
{
	if (!ft_strncmp(data->cmd[0], "/", 1))
	{
		if (access(data->cmd[0], X_OK) == -1)
		{
			if ((data->first == -1 && i == 2) || \
					(data->last == -1 && i == data->ac - 2))
				return (false);
			else
			{
				ft_putstr_fd("pipex: command not found\n", STDERR_FILENO);
				return (false);
			}
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
			if ((data->first == -1 && i == 2) || \
					(data->last == -1 && i == data->ac - 2))
				return (false);
			else
			{
				ft_putstr_fd("pipex: command not found1\n", STDERR_FILENO);
				return (false);
			}
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
			return (-1);
		mario_gaming(data, i);
		ft_free(data->cmd);
		i++;
	}
	data->cmd = ft_split(data->av[i], ' ');
	if (!data->cmd)
		return (-1);
	exit_code = get_out(data);
	ft_free(data->cmd);
	ft_free(data->path);
	return (exit_code);
}
