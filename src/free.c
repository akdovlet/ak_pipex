/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:41:28 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/13 17:02:02 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

void	clear_all(t_data *data)
{
	ft_free(data->path);
	ft_free(data->cmd);
	free(data->ids);
	data->ids = NULL;
	if (data->first > 0)
		close(data->first);
	if (data->last > 0)
		close(data->last);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	clear_exit(t_data *data, int exit_code)
{
	clear_all(data);
	exit(exit_code);
}
