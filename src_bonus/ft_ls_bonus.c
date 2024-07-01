/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:18:32 by corellan          #+#    #+#             */
/*   Updated: 2024/07/01 11:11:00 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static int	error_messages(t_ls *ls, t_erls error)
{
	if (error == FLAGSERR)
	{
		ft_dprintf(2, "ft_ls: illegal option -- %c\n", ls->char_flag);
		ft_dprintf(2, "usage: ft_ls [-GRadfglrtu1] [file ...]\n");
	}
	if (error == ALLOCERR)
		ft_dprintf(2, "ft_ls: %s\n", strerror(12));
	else if (error == CLOSEDSTDOUT)
		ft_dprintf(2, "ft_ls: stdout: %s\n", strerror(EBADF));
	free_lst(&(ls->dir), &(ls->file), &(ls->error));
	return (1);
}

int	main(int ac, char **av)
{
	t_ls	ls;

	ft_bzero(&ls, sizeof(ls));
	count_options(&ls, ac, av);
	if (valid_flag(&ls) == -1)
		return (error_messages(&ls, FLAGSERR));
	if (initialize_files_args(&ls) == -1)
		return (error_messages(&ls, ALLOCERR));
	sort_input(&ls, &(ls.error), 1);
	sort_input(&ls, &(ls.file), 0);
	sort_input(&ls, &(ls.dir), 0);
	if (print_files_or_error(&(ls.error), &ls, 1, ARGUMENT) == -1)
		return (error_messages(&ls, ALLOCERR));
	if (process_col(&ls, &(ls.file)) == -1 || \
		print_files_or_error(&(ls.file), &ls, 0, ARGUMENT) == -1)
		return (error_messages(&ls, ALLOCERR));
	ls.size_file_lst = ft_lstsize(ls.file);
	if (print_folder(&(ls.dir), &ls, 0) == -1)
		return (error_messages(&ls, ALLOCERR));
	if (write(1, "", 1) == -1)
		return (error_messages(&ls, CLOSEDSTDOUT));
	free_lst(&ls.dir, &ls.file, &ls.error);
	return (ls.exit_status);
}
