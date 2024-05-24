/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_col_format_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:47:11 by corellan          #+#    #+#             */
/*   Updated: 2024/05/24 14:28:52 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

int	print_col(t_ls *ls)
{
	struct winsize	ws;
	int				return_col;
	
	if (!((ls->flags_info >> COLFORM) & 1))
		return (0);
	return_col = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	if (return_col == -1)
		return (-1);
	ft_printf("SIZE OF THE WINDOW: %u\n", (unsigned int)ws.ws_col);
	return (0);
}
