/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:06:16 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/09 17:50:58 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
 #define FT_DPRINTF_H

# include "libft.h"

# define MAX_BUFFER 2048

typedef struct s_print
{
	char	*buffer;
	int		wrote;
	int		j;
	int		fd;
} t_print;

#endif
