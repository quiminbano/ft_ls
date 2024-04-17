/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:18:32 by corellan          #+#    #+#             */
/*   Updated: 2024/04/17 17:44:11 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	error_messages(t_ls *ls, t_erls error)
{
	if (error == FLAGSERR)
	{
		ft_dprintf(2, "ft_ls: illegal option -- %c\n", ls->char_flag);
		ft_dprintf(2, "usage: ft_ls [-Ralrt] [file ...]\n");
	}
	if (error == ALLOCERR)
		ft_dprintf(2, "ft_ls: memory allocation error\n");
	free_lst(ls->dir, ls->file, ls->error);
	return (1);
}

int	main(int ac, char **av)
{
	t_ls	ls;

	ft_bzero(&ls, sizeof(ls));
	ls.ac = ac;
	ls.av = av;
	count_options(&ls);
	if (ls.starting_point != 1 && valid_flag(&ls) == -1)
		return (error_messages(&ls, FLAGSERR));
	if (check_files_args(&ls) == -1)
		return (error_messages(&ls, ALLOCERR));
	if (print_files_or_error(&(ls.error), &ls, 1) == -1)
		return (error_messages(&ls, ALLOCERR));
	if (print_files_or_error(&(ls.file), &ls, 0) == -1)
		return (error_messages(&ls, ALLOCERR));
	if (print_folder(&(ls.dir), &ls) == -1)
		return (error_messages(&ls, ALLOCERR));
	free_lst(ls.dir, ls.file, ls.error);
	return (ls.exit_status);
}
