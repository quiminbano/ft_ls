/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_special_files_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:10:50 by corellan          #+#    #+#             */
/*   Updated: 2024/05/16 14:03:04 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#if __APPLE__ && __arm64__

void	padding_file_size(t_fileinfo *info, t_ls *ls)
{
	if (S_ISBLK(info->lstat.st_mode) || S_ISCHR(info->lstat.st_mode))
	{
		ls->len_size = ft_numlength_base((size_t)info->lstat.st_rdev, 16);
		ls->len_size += 2;
		if (ls->len_size > ls->pad.pad_size)
			ls->pad.pad_size = ls->len_size;
	}
	else
	{
		ls->len_size = ft_strlen(info->file_size);
		if (ls->len_size > ls->pad.pad_size)
			ls->pad.pad_size = ls->len_size;
	}
}

void	check_special_files(t_fileinfo *info, t_ls *ls)
{
	unsigned int	temp;

	temp = (unsigned int)info->lstat.st_rdev;
	if (S_ISBLK(info->lstat.st_mode) || S_ISCHR(info->lstat.st_mode))
		ft_printf("%#*x ", ls->pad.pad_size, temp);
	else
		ft_printf("%*s ", ls->pad.pad_size, info->file_size);
}
#else

void	padding_file_size(t_fileinfo *info, t_ls *ls)
{
	if (S_ISBLK(info->lstat.st_mode) || S_ISCHR(info->lstat.st_mode))
	{
		ls->pad.pad_major = 3;
		ls->pad.pad_minor = 3;
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

void	check_special_files(t_fileinfo *info, t_ls *ls)
{
	int	minor_dev;
	int	major_dev;

	minor_dev = minor(info->lstat.st_rdev);
	major_dev = major(info->lstat.st_rdev);
	if (S_ISBLK(info->lstat.st_mode) || S_ISCHR(info->lstat.st_mode))
	{
		ft_printf("%*d, ", ls->pad.pad_major, major_dev);
		if (minor_dev <= 255 && minor_dev >= 0)
			ft_printf("%*d ", ls->pad.pad_minor, minor_dev);
		else
			ft_printf("%#010x ", minor_dev);
	}
	else
		ft_printf("%*s ", ls->pad.pad_size, info->file_size);
}
#endif