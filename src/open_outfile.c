/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:09:42 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/19 19:09:48 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_outfile(t_data *data)
{
	if (data->here_doc_delimiter)
		data->outfile = open(data->outfile_name, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->outfile = open(data->outfile_name, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
