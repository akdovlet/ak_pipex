/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:37 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/15 01:32:15 by akdovlet         ###   ########.fr       */
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

# define HARDPATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef struct	s_data
{
	pid_t	*ids;
	char	**path;
	char	**av;
	char	**env;
	char	**cmd;
	int		fd[2];
	int		first;
	int		last;
	int		ac;
	int		hermes;
	int		cmd_count;
	int		exit_code;
	int		here_doc;
}	t_data;

/******************************check_file.c***********************************/
int		check_file(char *file);



void	dr_here(t_data *data);
int		ft_strcmp(char *s1, char *s2);

/********************************free.c***************************************/
void	ft_free(char **str);
void	clear_all(t_data *data);
void	clear_exit(t_data *data, int exit_code);

/******************************ak_pipe.c*********************************/
void	ak_pipe(t_data *data, int i);
void	ak_pipeout(t_data *data, int i);



char	**parse_env(char **env);
bool	file_access(char *file, int check);
void	find_exec(char *cmd, t_data *data);

/******************************check_file.c***********************************/

char	**px_split(char const *s, char c);

/******************************seek_and_execute.c*****************************/
void	seek_and_execute(t_data	*data);
void	cmd_exe(t_data *data);

/******************************setup.c****************************************/
bool	setup(t_data *data, int ac, char **av, char **env);
#endif
