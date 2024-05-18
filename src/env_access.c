/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:52:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/18 22:54:01 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	file_access(char *file, int check)
{
	if (!access(file, check))
		return (true);
	return (false);
}

char	**get_path_from_env(char **env)
{
	int	i;

	i = 0;
	if (!env[0])
		return (px_split(HARDPATH, ':'));
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
			return (px_split(env[i] + 5, ':'));
		i++;
	}
	return (ft_split("./", '\0'));
}
