/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:20 by akdovlet          #+#    #+#             */
/*   Updated: 2024/04/25 20:38:32 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

//open, close, read, write,
// malloc, free, perror, access
// strerror, env, dup, dup2,
// execve, exit, fork, pipe,
// unlink, wait, waitpid
int main(int ac, char **av, char **env)
{
	int		i;
	int		id;
	t_data	data;
	int		fd[2];

	if (ac < 5 || !parse_and_check(ac, av, env, &data))
		return (1);
	id = fork();
	if (pipe(fd) == -1)
		return (perror("pipex"), 1);
	if (id != 0)
		printf("here\n");
	return (0);
}
