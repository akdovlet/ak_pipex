/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:52:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/12 23:37:53 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

bool	file_access(char *file, int check)
{
	if (!access(file, check))
		return (true);
	return (false);
}

char	**parse_env(char **env)
{
	int	i;

	i = 0;
	if (!env[0])
	{
		
		return (px_split(HARDPATH, ':'));
	}
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
			return (px_split(env[i] + 5, ':'));
		i++;
	}
	return (ft_split("./", '\0'));
}

bool	find_exec(char *cmd, t_data *data)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = NULL;
	while (data->path[i])
	{
		full_path = ft_strjoin(data->path[i], cmd);
		if (!full_path)
			return (false);
		if (!access(full_path, X_OK))
		{
			execve(full_path, data->cmd, data->env);
			free(full_path);
			exit(EXIT_FAILURE);
			return (false);
		}
		free(full_path);
		i++;
	}
	return (false);
}
