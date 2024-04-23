/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_dir_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:43:55 by corellan          #+#    #+#             */
/*   Updated: 2024/04/23 17:27:19 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	dir_lst(t_list **fil, t_ls *ls, struct dirent *dat, char *dir)
{
	t_list	*tmp;

	ls->tmpinter = ft_strjoin(dir, "/");
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
	ft_lstadd_back(fil, tmp);
	ls->last = tmp;
	return (0);
}

int	loop_dir(t_fileinfo *info, t_ls *ls, t_dircol *col, DIR **tmpdir)
{
	struct dirent	*data;
	t_fileinfo		*last;

	while (1)
	{
		data = readdir((*tmpdir));
		if (!data)
			break ;
		if (dir_lst(&(col->files), ls, data, info->name) == -1)
		{
			closedir(*tmpdir);
			return (-1);
		}
		last = ls->last->content;
		if (((ls->flags_info >> RECFLAG) & 1) && \
			S_ISDIR(last->lstat.st_mode) && ft_strcmp(".", last->name) && \
			ft_strcmp("..", last->name) && \
			dir_lst(&(col->dir), ls, data, info->name) == -1)
		{
			closedir(*tmpdir);
			return (-1);
		}
	}
	return (0);
}
