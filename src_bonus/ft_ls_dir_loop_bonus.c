/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_dir_loop_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:43:55 by corellan          #+#    #+#             */
/*   Updated: 2024/05/26 20:57:09 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static void	app_dir(t_ls *ls, t_fileinfo *inf)
{
	if (inf->rel_path)
		ls->tmpinter = ft_strjoin(inf->rel_path, "/");
	else if (inf->name && !ft_strcmp(inf->name, "/"))
		ls->tmpinter = ft_strjoin("", "/");
	else
		ls->tmpinter = ft_strjoin(inf->name, "/");
}

static int	dir_lst(t_list **fil, t_ls *ls, struct dirent *dat, t_fileinfo *inf)
{
	t_list	*tmp;

	app_dir(ls, inf);
	if (!ls->tmpinter)
	{
		free_lst(NULL, fil, NULL);
		return (-1);
	}
	tmp = process_argument(ls, dat->d_name, DIRECTORY);
	if (!tmp)
	{
		free_lst(NULL, fil, NULL);
		if (ls->tmpinter)
			free(ls->tmpinter);
		ls->tmpinter = NULL;
		return (-1);
	}
	if (ls->stat_status != -1)
		ft_lstadd_back(fil, tmp);
	ls->last = tmp;
	return (0);
}

static int	is_rec(t_fileinfo *last, t_ls *ls)
{
	if (!((ls->flags_info >> RECFLAG) & 1))
		return (0);
	if (!S_ISDIR(last->lstat.st_mode))
		return (0);
	if (!ft_strcmp(".", last->name) || !ft_strcmp("..", last->name))
		return (0);
	return (1);
}

int	loop_dir(t_fileinfo *info, t_ls *ls, t_dircol *col, DIR **tmpdir)
{
	struct dirent	*data;

	while (1)
	{
		data = readdir((*tmpdir));
		if (!data)
			break ;
		if (!((ls->flags_info >> AFLAG) & 1) && data->d_name[0] == '.')
			continue ;
		if (dir_lst(&(col->files), ls, data, info) == -1)
		{
			closedir(*tmpdir);
			return (-1);
		}
		if (ls->stat_status == -1)
			ft_lstadd_back(&(col->err), ls->last);
		if (is_rec((t_fileinfo *)(ls->last->content), ls) && \
			dir_lst(&(col->dir), ls, data, info) == -1)
		{
			closedir(*tmpdir);
			return (-1);
		}
	}
	return (0);
}
