/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:09:57 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/19 19:23:18 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infile_setup(t_data *data, char **av)
{
	data->infile = infile_check(av[1]);
	if (data->infile == -1)
	{
		data->hermes = open("/dev/null", O_RDONLY);
		if (data->hermes < 0)
			return (perror(av[1]), ft_free(data->path), exit(EXIT_FAILURE));
	}
	else
		data->hermes = data->infile;
}

int	infile_check(char *file)
{
	int	fd;

	if (!file_access(file, R_OK))
	{
		ft_dprintf(STDERR, ERR_MSG, file, strerror(errno));
		return (-1);
	}
	else
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			ft_dprintf(STDERR, ERR_MSG, file, strerror(errno));
			return (-1);
		}
	}
	return (fd);
}
