/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:18:32 by corellan          #+#    #+#             */
/*   Updated: 2024/04/13 22:42:39 by corellan         ###   ########.fr       */
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
	if (check_files_args(&ls) == -1)
		return (1);
	print_error(&(ls.error), &ls);
	free_lst(ls.dir, ls.file, ls.error);
	return (ls.exit_status);
}
