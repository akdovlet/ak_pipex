/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:41:38 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/17 18:22:35 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infile_setup(t_data *data, char **av)
{
	data->first = check_file(av[1]);
	if (data->first == -1)
	{
		data->hermes = open("/dev/null", O_RDONLY);
		if (data->hermes < 0)
			return (perror(av[1]), ft_free(data->path), exit(EXIT_FAILURE));
	}
	else
		data->hermes = data->first;
}

bool	setup(t_data *data, int ac, char **av, char **env)
{
	*data = (t_data) {0};
	data->ac = ac;
	data->av = av;
	data->env = env;
	data->output_file = av[ac - 1];
	data->commands = &av[2];
	data->here_doc_delimiter = NULL;
	data->path = parse_env(env);
	if (!data->path)
		return (perror("pipex"), false);
	if (!ft_strcmp("here_doc", av[1]))
		data->here_doc_delimiter = av[2];
	else
		infile_setup(data, av);
	data->command_count = ac - (data->here_doc_delimiter != NULL);
	return (true);
}
