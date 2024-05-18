/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:41:38 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/18 23:16:19 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file(char *file)
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

void	infile_setup(t_data *data, char **av)
{
	data->infile = check_file(av[1]);
	if (data->infile == -1)
	{
		data->hermes = open("/dev/null", O_RDONLY);
		if (data->hermes < 0)
			return (perror(av[1]), ft_free(data->path), exit(EXIT_FAILURE));
	}
	else
		data->hermes = data->infile;
}

void	setup(t_data *data, int ac, char **av, char **env)
{
	*data = (t_data){0};
	data->env = env;
	data->path = get_path_from_env(env);
	if (!data->path)
		return (perror("malloc"), exit(1));
	if (!ft_strcmp("here_doc", av[1]))
		data->here_doc_delimiter = av[2];
	else
		infile_setup(data, av);
	data->outfile_name = av[ac - 1];
	av[ac - 1] = NULL;
	data->commands = &av[2 + (data->here_doc_delimiter != NULL)];
	data->cmd_count = ac - (3 + (data->here_doc_delimiter != NULL));
}
