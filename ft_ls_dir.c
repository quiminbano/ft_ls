/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:34:27 by corellan          #+#    #+#             */
/*   Updated: 2024/04/22 17:20:39 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*dir_lst(t_list **fil, t_ls *ls, struct dirent *dat, char *dir)
{
	t_list	*tmp;

	ls->tmpinter = ft_strjoin(dir, "/");
	if (!ls->tmpinter)
	{
		free_lst(NULL, fil, NULL);
		return (NULL);
	}
	tmp = process_argument(ls, dat->d_name, DIRECTORY);
	if (!tmp)
	{
		free_lst(NULL, fil, NULL);
		if (ls->tmpinter)
			free(ls->tmpinter);
		ls->tmpinter = NULL;
		return (NULL);
	}
	return (tmp);
}

static int	loop_dir(t_fileinfo *info, t_ls *ls, t_dircol *col, DIR **tmpdir)
{
	struct dirent	*data;
	t_list			*last;
	t_fileinfo		*tmp_d;

	last = NULL;
	while (1)
	{
		data = readdir((*tmpdir));
		if (!data)
			break ;
		last = dir_lst(&(col->files), ls, data, info->name);
		if (!last)
		{
			closedir(*tmpdir);
			return (-1);
		}
		ft_lstadd_back(&(col->files), last);
		tmp_d = last->content;
		if (((ls->flags_info >> RECFLAG) & 1) && S_ISDIR(tmp_d->lstat.st_mode))
			ft_lstadd_back(&(col->dir), last);
	}
	return (0);
}

static int	process_folder(t_fileinfo *info, t_ls *ls)
{
	t_dircol	col;
	DIR			*tmpdir;

	ft_bzero(&(col), sizeof(col));
	tmpdir = opendir(info->name);
	if (!tmpdir)
		return (-1);
	if (loop_dir(info, ls, &col, &tmpdir) == -1)
		return (-1);
	sort_input(ls, &(col.files), 0);
	sort_input(ls, &(col.dir), 0);
	closedir(tmpdir);
	if (print_files_or_error(&(col.files), ls, 0, DIRECTORY) == -1)
		ls->exit_status = -1;
	free_lst(NULL, &(col.files), NULL);
	if (col.dir)
		free(col.dir);
	return (ls->exit_status);
}

int	print_folder(t_list **begin, t_ls *ls, int flag)
{
	t_list		*tmp;
	t_fileinfo	*info;
	int			size_lst;

	tmp = *begin;
	if (!tmp)
		return (0);
	size_lst = ft_lstsize(tmp);
	while (tmp)
	{
		info = tmp->content;
		if ((size_lst > 1 || flag) && info->rel_path)
			ft_printf("%s:\n", info->rel_path);
		else if ((size_lst > 1 || flag) && info->name)
			ft_printf("%s:\n", info->name);
		if (process_folder(info, ls) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
