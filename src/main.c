/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:20 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/11 14:51:01 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// open, close, read, write,
// malloc, free, perror, access
// strerror, env, dup, dup2
// execve, exit, fork, pipe,
// unlink, wait, waitpid
// if no path, try access with current dir
// if no env, try access with /usr/bin/
// wait as many times as you have cmds
// Pipe execute toutes les commandes, essaie d'ouvrir tous les fichier
// Il ne s'arrete pas a la premiere erreur. Va afficher les erreurs par
// bloc, et va afficher en priorite les erreurs de file.
// Si une commande n'existe pas il va essayer d'executer la prochaine
// Si il n'y a pas d'infile, la commande ne va pas s'executer et tout
// l'output sera vide et pipe renvoie 1
int main(int ac, char **av, char **env)
{
	int		i;
	int		exit_code;
	t_data	data;

	i = 2;
	// if (ac < 4)
	// {
	// 	ft_putstr_fd("Error: Invalid number of arguments\n", STDERR_FILENO);
	// 	return (1);
	// }
	if (!setup(&data, ac, av, env))
		return (1);
	exit_code = seek_and_execute(&data);
	return (exit_code);
}

// int main()
// {
// 	char **strs;
	
// 	strs = ft_split("./", '\0');
// 	printf("%s\n", strs[0]);
// 	printf("%s\n", strs[1]);
// }
