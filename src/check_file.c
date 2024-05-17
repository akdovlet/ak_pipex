/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:36:19 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/17 16:00:10 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file(char *file)
{
	int	fd;

	if (!file_access(file, R_OK))
	{
		ft_dprintf(2, "pipex: %s: %s\n", file, strerror(errno));
		return (-1);		
	}
	else
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			return (perror(file), -1);
	}
	return (fd);
}
