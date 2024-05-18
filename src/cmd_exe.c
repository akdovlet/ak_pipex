/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:39:03 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/18 23:19:53 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	nopath_exec(char *cmd, t_data *data)
{
	if (access(cmd, X_OK) == -1)
	{
		ft_dprintf(STDERR, ERR_MSG, cmd, strerror(errno));
		free(cmd);
		clear_exit(data, 126);
	}
	execve(cmd, data->cmd, data->env);
	ft_dprintf(STDERR, ERR_MSG, cmd, strerror(errno));
	free(cmd);
	clear_exit(data, 127);
}

void	nopath_run(char *cmd, t_data *data)
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
		if (!access(full_path, F_OK))
			nopath_exec(full_path, data);
		free(full_path);
		i++;
	}
	ft_dprintf(STDERR, ERR_CMD, data->cmd[0]);
	clear_exit(data, 127);
}

void	path_run(char *cmd, t_data *data)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_dprintf(STDERR, ERR_MSG, cmd, strerror(errno));
		clear_exit(data, 127);
	}
	else if (access(cmd, X_OK) == -1)
	{
		ft_dprintf(STDERR, ERR_MSG, cmd, strerror(errno));
		clear_exit(data, 126);
	}
	execve(cmd, data->cmd, data->env);
	clear_exit(data, 127);
}

void	cmd_exe(t_data *data)
{
	if (!data->cmd[0])
	{
		ft_dprintf(STDERR, ERR_CMD, data->cmd[0], strerror(errno));
		clear_exit(data, 127);
	}
	if (ft_strchr(data->cmd[0], '/'))
		path_run(data->cmd[0], data);
	else
		nopath_run(data->cmd[0], data);
}
