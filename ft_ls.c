/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:18:32 by corellan          #+#    #+#             */
/*   Updated: 2024/04/09 23:14:18 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	t_ls	ls;

	ft_bzero(&ls, sizeof(ls));
	ls.ac = ac;
	ls.av = av;
	count_options(&ls);
	if (ls.starting_point != 1 && valid_flag(&ls) == -1)
	{
		ft_dprintf(2, "ft_ls: illegal option -- %c\n", ls.char_flag);
		ft_dprintf(2, "usage: ft_ls [-Ralrt] [file ...]\n");
		return (1);
	}
	return (0);
}
