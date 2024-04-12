/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by corellan          #+#    #+#             */
/*   Updated: 2024/04/12 16:57:01 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	process_one_argument(t_ls *ls)
{
	int			stat_res;
	t_list		*tmp;
	t_fileinfo	*info;

	ls->tmpdir = ft_strdup(".");
	if (!ls->tmpdir)
		return (-1);
	info = (t_fileinfo *)malloc(sizeof(t_fileinfo));
	if (!info)
	{
		free(ls->tmpdir);
		return (-1);
	}
	ft_bzero(info, sizeof(*info));
	stat_res = stat(".", &info->stat);
	if (stat_res == -1)
		return (-1);
	tmp = ft_lstnew(info);
	if (!tmp)
	{
		free(ls->tmpdir);
		free(tmp);
		return (-1);
	}
	return (0);
}

int	check_files_args(t_ls *ls)
{
	DIR		*tmpdir;
	size_t	i;
	int		stat_return;

	i = ls->starting_point;
	tmpdir = NULL;
	if (ls->ac == 1)
		return (process_one_argument(ls));
	return (0);
}
