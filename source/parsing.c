/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:52:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/04/26 20:43:55 by akdovlet         ###   ########.fr       */
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

bool	find_exec(char *cmd, t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (data->path[i])
	{
		path = ft_strjoin(data->path[i], cmd);
		if (file_access(path, X_OK))
		{
			data->cmd = path;
			return (true);
		}
		free(path);
		i++;
	}
	return (false);
}


bool	check_files(char *infile, char *outfile, t_data *data)
{
	if (!file_access(infile, R_OK))
		return (perror("pipex"), false);
	else
	{
		data->fd[0] = open(infile, O_RDONLY);
		if (data->fd[0] < 0)
			return (perror("pipex"), false);
	}
	if (!file_access(outfile, F_OK))
	{
		data->fd[1] = open(outfile, O_CREAT);
		if (data->fd[1] < 0)
			return (close(data->fd[0]), perror("pipex"), false);
	}
	else if (file_access(outfile, R_OK))
	{
		data->fd[1] = open(outfile, O_APPEND);
		if (data->fd[1] < 0)
			return (close(data->fd[0]), perror("pipex"), false);
	}
	else
		return (perror("pipex"), false);
	return (true);
}

// Pipe execute toutes les commandes, essaie d'ouvrir tous les fichier
// Il ne s'arrete pas a la premiere erreur. Va afficher les erreurs par
// bloc, et va afficher en priorite les erreurs de file.
// Si une commande n'existe pas il va essayer d'executer la prochaine
// Si il n'y a pas d'infile, la commande ne va pas s'executer et tout
// l'output sera vide et pipe renvoie 1
bool	parse_and_check(int ac, char **av, char **env, t_data *data)
{
	int		fd;
	char	*path;
	char	**spath;

	if (!check_files(av[1], av[ac -1], data))
		return (false);
	path = parse_env(env);
	if (!path)
		return (perror("pipex"), false);
	data->path = px_split(path, ':');
	if (!data->path)
		return (ft_putstr_fd("pipex: split failed\n", STDERR_FILENO), false);
	if (!find_exec(av[2], data))
		return (perror("pipexsss"), free(data->path), false);
	printf("%s\n", data->cmd);
	return (true);
}
