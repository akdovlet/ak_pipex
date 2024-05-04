/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:37 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/04 13:12:35 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include "libft.h"

typedef struct	s_data
{
	char	**path;
	char	*cmd;	
	int		fd[2];
}	t_data;

char	*parse_env(char **env);
bool	file_access(char *file, int check);
bool	parse_and_check(int ac, char **av, char **env, t_data *data);

char	**px_split(char const *s, char c);

#endif
