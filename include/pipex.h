/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:37 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/07 20:00:00 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

typedef struct	s_data
{
	char	**path;
	char	**av;
	char	**env;
	char	**cmd;
	int		first;
	int		last;
	int		ac;
	int		hermes;
	int		fd[2];
}	t_data;

/******************************check_file.c***********************************/
int	check_file(char *file);

/********************************free.c***************************************/
void	ft_free(char **str);

/******************************mario_gaming.c*********************************/
void	mario_gaming(t_data *data, int i);
int	get_out(t_data *data);



char	**parse_env(char **env);
bool	file_access(char *file, int check);
bool	parse_and_check(int ac, char **av, char **env, t_data *data);
bool	find_exec(char *cmd, t_data *data);

/******************************check_file.c***********************************/

char	**px_split(char const *s, char c);

/******************************seek_and_execute.c*****************************/
int		seek_and_execute(t_data	*data);
bool	cmd_exe(t_data *data, int i);

/******************************setup.c****************************************/
void	setup(t_data *data, int ac, char **av, char **env);
#endif
