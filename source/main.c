/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:20 by akdovlet          #+#    #+#             */
/*   Updated: 2024/04/23 18:34:16 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

//open, close, read, write,
// malloc, free, perror, access
// strerror, env, dup, dup2,
// execve, exit, fork, pipe,
// unlink, wait, waitpid

int main(int ac, char **av, char **env)
{
	int		i;
	int		id;
	int		fd[2];
	(void)ac;
	(void)av;

	i = 0;
	if (ac == 1)
		return (0);
	if (pipe(fd) == -1)
	{
		printf("Pipe Error\n");
		return (1);
	}
	id = fork();
	if (id == 0)
		printf("%s\n", parse_env(env));
		// while (env[i])
		// 	printf("%s\n", env[i++]);
	if (id != 0)
		wait(NULL);
	return (1);
}
