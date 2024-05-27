/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:39:03 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/27 09:35:21 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_exe(t_data *data)
{
	if (!data->cmd[0])
	{
		ft_dprintf(STDERR, ERR_CMD, data->cmd[0], strerror(errno));
		clear_all_exit(data, 127);
	}
	if (ft_strchr(data->cmd[0], '/'))
		path_run(data->cmd[0], data);
	else
		nopath_run(data->cmd[0], data);
}

void	path_run(char *cmd, t_data *data)
{
	if (!file_access(cmd, F_OK))
	{
		ft_dprintf(STDERR, ERR_MSG, cmd, strerror(errno));
		clear_all_exit(data, 127);
	}
	else if (!file_access(cmd, X_OK))
	{
		ft_dprintf(STDERR, ERR_MSG, cmd, strerror(errno));
		clear_all_exit(data, 126);
	}
	execve(cmd, data->cmd, data->env);
	clear_all_exit(data, 127);
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
			return (clear_all_exit(data, EXIT_FAILURE));
		if (file_access(full_path, F_OK))
			nopath_exec(full_path, data);
		free(full_path);
		i++;
	}
	ft_dprintf(STDERR, ERR_CMD, data->cmd[0]);
	clear_all_exit(data, 127);
}

void	nopath_exec(char *full_path, t_data *data)
{
	if (!file_access(full_path, X_OK))
	{
		ft_dprintf(STDERR, ERR_MSG, full_path, strerror(errno));
		free(full_path);
		clear_all_exit(data, 126);
	}
	execve(full_path, data->cmd, data->env);
	ft_dprintf(STDERR, ERR_MSG, full_path, strerror(errno));
	free(full_path);
	clear_all_exit(data, 127);
}
