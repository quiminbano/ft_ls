/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_fill_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by corellan          #+#    #+#             */
/*   Updated: 2024/04/18 21:58:06 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_info(t_fileinfo **info, t_ls *ls, t_lstls type)
{
	(*info)->name = ls->tmpdir;
	ls->tmpdir = NULL;
	if (type == ARGUMENT)
		ls->stat_status = lstat((*info)->name, &((*info)->lstat));
	else
		ls->stat_status = lstat((*info)->rel_path, &((*info)->lstat));
	if (ls->stat_status != -1)
	{
		(*info)->pw = getpwuid((*info)->lstat.st_uid);
		(*info)->gr = getgrgid((*info)->lstat.st_gid);
		(*info)->file_size = ft_lltoa((*info)->lstat.st_size);
		if (!(*info)->file_size)
		{
			delete_fileinfo((*info));
			(*info) = NULL;
			return (-1);
		}
	}
	return (0);
}

t_list	*process_argument(t_ls *ls, const char *input, t_lstls type)
{
	t_list		*tmp;
	t_fileinfo	*info;

	ls->tmpdir = ft_strdup(input);
	if (!ls->tmpdir)
		return (NULL);
	info = (t_fileinfo *)ft_calloc(1, sizeof(t_fileinfo));
	if (!info)
	{
		free(ls->tmpdir);
		ls->tmpdir = NULL;
		return (NULL);
	}
	if (fill_info(&info, ls, type) == -1)
		return (NULL);
	tmp = ft_lstnew(info);
	if (!tmp)
	{
		delete_fileinfo(info);
		info = NULL;
		return (NULL);
	}
	return (tmp);
}

static int	process_one_argument(t_ls *ls, const char *str)
{
	t_list	*tmp;

	tmp = NULL;
	tmp = process_argument(ls, str, ARGUMENT);
	if (!tmp)
		return (-1);
	ft_lstadd_back(&(ls->dir), tmp);
	return (0);
}

int	check_files_args(t_ls *ls)
{
	size_t	i;
	t_list	*tmp;

	i = ls->starting_point;
	if (ls->ac == 1 || (ls->ac == 2 && ls->av[1][0] == '-'))
		return (process_one_argument(ls, "."));
	while ((int)i < ls->ac)
	{
		tmp = NULL;
		tmp = process_argument(ls, ls->av[i], ARGUMENT);
		if (!tmp)
			return (free_lst(&(ls->dir), &(ls->file), &(ls->error)));
		if (ls->stat_status == -1)
			ft_lstadd_back(&(ls->error), tmp);
		else if (S_ISDIR(((t_fileinfo *)tmp->content)->lstat.st_mode))
			ft_lstadd_back(&(ls->dir), tmp);
		else
			ft_lstadd_back(&(ls->file), tmp);
		i++;
	}
	sort_input(ls, &(ls->error), 1);
	sort_input(ls, &(ls->file), 0);
	sort_input(ls, &(ls->dir), 0);
	return (0);
}
