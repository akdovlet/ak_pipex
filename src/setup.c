/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:41:38 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/11 14:48:02 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	setup(t_data *data, int ac, char **av, char **env)
{
	data->path = parse_env(env);
	if (!data->path)
	{
		ft_dprintf(STDERR_FILENO, "pipex: malloc failed\n");
		return (false);
	}
	data->first = check_file(av[1]);
	if (data->first == -1)
	{
		data->hermes = open("/dev/null", O_RDONLY);
		if (data->hermes < 0)
			return (perror("pipex"), false);
	}
	else
		data->hermes = data->first;
	data->last = 0;
	data->cmd = NULL;
	data->ac = ac;
	data->av = av;
	data->env = env;
	return (true);
}
