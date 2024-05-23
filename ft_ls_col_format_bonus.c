/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_col_format_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:47:11 by corellan          #+#    #+#             */
/*   Updated: 2024/05/23 15:22:29 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

int	print_col(t_ls *ls)
{
	struct termios	ws;
	int				return_col;
	
	if (!((ls->flags_info >> COLFORM) & 1))
		return (0);
	return_col = tcgetattr(STDIN_FILENO, &ws);
	ft_printf("THIS IS THE VALUE OF col: %d\n", return_col);
	if (return_col == -1)
		return (-1);
	return (0);
}
