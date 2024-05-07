/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:52:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/07 02:06:25 by akdovlet         ###   ########.fr       */
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
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
			return (px_split(env[i] + 5, ':'));
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
		if (!path)
			return (false);
		if (!access(path, X_OK))
		{
			execve(path, data->cmd, data->env);
			free(path);
			exit(EXIT_FAILURE);
			return (false);
		}
		free(path);
		i++;
	}
	return (false);
}



// 	if (!file_access(outfile, F_OK))
// 	{
// 		data->fd[1] = open(outfile, O_CREAT);
// 		if (data->fd[1] < 0)
// 			return (close(data->fd[0]), perror("pipex"), false);
// 	}
// 	else if (file_access(outfile, R_OK))
// 	{
// 		data->fd[1] = open(outfile, O_APPEND);
// 		if (data->fd[1] < 0)
// 			return (close(data->fd[0]), perror("pipex"), false);
// 	}
// 	else
// 		return (perror("pipex"), false);
// 	return (true);
// }

// Pipe execute toutes les commandes, essaie d'ouvrir tous les fichier
// Il ne s'arrete pas a la premiere erreur. Va afficher les erreurs par
// bloc, et va afficher en priorite les erreurs de file.
// Si une commande n'existe pas il va essayer d'executer la prochaine
// Si il n'y a pas d'infile, la commande ne va pas s'executer et tout
// l'output sera vide et pipe renvoie 1
