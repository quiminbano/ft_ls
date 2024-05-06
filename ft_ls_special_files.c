/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_special_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:10:50 by corellan          #+#    #+#             */
/*   Updated: 2024/04/30 17:20:42 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#if __APPLE__ && __arm64__

void	padding_file_size(t_fileinfo *info, t_ls *ls)
{
	size_t	size;

	size = 0;
	if (S_ISBLK(info->lstat.st_mode) || S_ISCHR(info->lstat.st_mode))
	{
		size = ft_numlength_base(major(info->lstat.st_rdev), 10);
		if (size > ls->pad.pad_major)
			ls->pad.pad_major = size;
		size = 0;
		size = ft_numlength_base(minor(info->lstat.st_rdev), 10);
		if (size > ls->pad.pad_minor)
			ls->pad.pad_minor = size;
		if ((ls->pad.pad_major + ls->pad.pad_minor + 2) >= ls->pad.pad_size)
			ls->pad.pad_size = (ls->pad.pad_major + ls->pad.pad_minor + 2);
		else
			ls->pad.pad_major = ls->pad.pad_size - ls->pad.pad_minor - 2;
	}
	else
	{
		ls->len_size = ft_strlen(info->file_size);
		if (ls->len_size > ls->pad.pad_size)
			ls->pad.pad_size = ls->len_size;
	}
}
#else

void	padding_file_size(t_fileinfo *info, t_ls *ls)
{
	size_t	size;

	size = 0;
	if (S_ISBLK(info->lstat.st_mode) || S_ISCHR(info->lstat.st_mode))
	{
		size = ft_numlength_base(major(info->lstat.st_rdev), 10);
		if (size > ls->pad.pad_major)
			ls->pad.pad_major = size;
		size = 0;
		size = ft_numlength_base(minor(info->lstat.st_rdev), 10);
		if (size > ls->pad.pad_minor)
			ls->pad.pad_minor = size;
		if ((ls->pad.pad_major + ls->pad.pad_minor + 2) >= ls->pad.pad_size)
			ls->pad.pad_size = (ls->pad.pad_major + ls->pad.pad_minor + 2);
		else
			ls->pad.pad_major = ls->pad.pad_size - ls->pad.pad_minor - 2;
	}
	else
	{
		ls->len_size = ft_strlen(info->file_size);
		if (ls->len_size > ls->pad.pad_size)
			ls->pad.pad_size = ls->len_size;
	}
}
#endif