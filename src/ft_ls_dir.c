/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:34:27 by corellan          #+#    #+#             */
/*   Updated: 2024/06/19 12:53:57 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_error_folder(t_fileinfo *info, t_ls *ls)
{
	int	check_error;

	check_error = info->er_st;
	if (!check_error && S_ISDIR(info->lstat.st_mode) && info->er_dr == EBADF)
		ft_dprintf(2, "ft_ls: %s: directory causes a cycle\n", info->name);
	else if (info->name)
		ft_dprintf(2, "ft_ls: %s: %s\n", info->name, strerror(info->er_dr));
	ls->exit_status = 1;
}

static void	open_directory(t_fileinfo *info, DIR **tmpdir)
{
	if (info->rel_path)
		(*tmpdir) = opendir(info->rel_path);
	else
		(*tmpdir) = opendir(info->name);
}

static int	process_folder(t_fileinfo *info, t_ls *ls)
{
	t_dircol	col;
	int			return_dir;
	DIR			*tmpdir;

	return_dir = 0;
	ft_bzero(&(col), sizeof(col));
	open_directory(info, &tmpdir);
	if (!tmpdir)
		info->er_dr = errno;
	if (!tmpdir && info->er_dr == ENOMEM)
		return (-1);
	if (!tmpdir)
		return (-2);
	if (loop_dir(info, ls, &col, &tmpdir) == -1)
		return (-1);
	sort_input(ls, &(col.files), 0);
	sort_input(ls, &(col.dir), 0);
	closedir(tmpdir);
	if (print_files_or_error(&(col.files), ls, 0, DIRECTORY) == -1)
		return_dir = -1;
	if (print_folder(&(col.dir), ls, 1))
		return_dir = -1;
	free_lst(&(col.dir), &(col.files), &(col.err));
	return (return_dir);
}

static void	print_path(t_fileinfo *info, t_ls *ls, int flag, int size_lst)
{
	if ((size_lst > 1 || flag || ls->size_file_lst) && info->rel_path && \
		!ls->nofirst_dir)
		ft_printf("%s:\n", info->rel_path);
	else if ((size_lst > 1 || flag || ls->size_file_lst) && info->name && \
		!ls->nofirst_dir)
		ft_printf("%s:\n", info->name);
	else if ((size_lst > 1 || flag || ls->size_file_lst) && info->rel_path)
		ft_printf("\n%s:\n", info->rel_path);
	else if ((size_lst > 1 || flag || ls->size_file_lst) && info->name)
		ft_printf("\n%s:\n", info->name);
	ls->nofirst_dir = 1;
}

int	print_folder(t_list **begin, t_ls *ls, int flag)
{
	t_list		*tmp;
	t_fileinfo	*info;
	int			size_lst;
	int			return_dir;

	tmp = *begin;
	if (!tmp)
		return (0);
	size_lst = ft_lstsize(tmp);
	while (tmp)
	{
		info = tmp->content;
		print_path(info, ls, flag, size_lst);
		return_dir = process_folder(info, ls);
		if (return_dir == -1)
			return (-1);
		else if (return_dir == -2)
			print_error_folder(info, ls);
		tmp = tmp->next;
	}
	return (0);
}
