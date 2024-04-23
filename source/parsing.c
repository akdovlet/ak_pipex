/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:52:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/04/23 18:48:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
 #include <fcntl.h>
 
char	*parse_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}



int	parse_and_check(int ac, char **av, char **env)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
}



