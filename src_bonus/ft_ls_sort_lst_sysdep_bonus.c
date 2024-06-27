/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_lst_sysdep_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:18:53 by corellan          #+#    #+#             */
/*   Updated: 2024/06/27 18:38:44 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#ifdef __linux__

int	check_rev(t_fileinfo *inf, t_fileinfo *nxt, unsigned int bk)
{
	const unsigned int	time = ((bk >> TFLAG) & 1);
	const unsigned int	la = ((bk >> UFLAG) & 1);

	if (!time && ft_strcmp(inf->name, nxt->name) <= -1)
		return (1);
	else if (time && !la && inf->lstat.st_mtime == nxt->lstat.st_mtime && \
		inf->lstat.st_mtim.tv_nsec == nxt->lstat.st_mtim.tv_nsec && \
		ft_strcmp(inf->name, nxt->name) <= -1)
		return (1);
	else if (time && !la && inf->lstat.st_mtime == nxt->lstat.st_mtime && \
		inf->lstat.st_mtim.tv_nsec > nxt->lstat.st_mtim.tv_nsec)
		return (1);
	else if (time && !la && inf->lstat.st_mtime > nxt->lstat.st_mtime)
		return (1);
	else if (time && la && inf->lstat.st_atime == nxt->lstat.st_atime && \
		inf->lstat.st_atim.tv_nsec == nxt->lstat.st_atim.tv_nsec && \
		ft_strcmp(inf->name, nxt->name) <= -1)
		return (1);
	else if (time && la && inf->lstat.st_atime == nxt->lstat.st_atime && \
		inf->lstat.st_atim.tv_nsec > nxt->lstat.st_atim.tv_nsec)
		return (1);
	else if (time && la && inf->lstat.st_atime > nxt->lstat.st_atime)
		return (1);
	return (0);
}

int	check_norev(t_fileinfo *inf, t_fileinfo *nxt, unsigned int bk)
{
	const unsigned int	time = ((bk >> TFLAG) & 1);
	const unsigned int	la = ((bk >> UFLAG) & 1);

	if (!time && ft_strcmp(inf->name, nxt->name) >= 1)
		return (1);
	else if (time && !la && inf->lstat.st_mtime == nxt->lstat.st_mtime && \
		inf->lstat.st_mtim.tv_nsec == nxt->lstat.st_mtim.tv_nsec && \
		ft_strcmp(inf->name, nxt->name) >= 1)
		return (1);
	else if (time && !la && inf->lstat.st_mtime == nxt->lstat.st_mtime && \
		inf->lstat.st_mtim.tv_nsec < nxt->lstat.st_mtim.tv_nsec)
		return (1);
	else if (time && !la && inf->lstat.st_mtime < nxt->lstat.st_mtime)
		return (1);
	else if (time && la && inf->lstat.st_atime == nxt->lstat.st_atime && \
		inf->lstat.st_atim.tv_nsec == nxt->lstat.st_atim.tv_nsec && \
		ft_strcmp(inf->name, nxt->name) >= 1)
		return (1);
	else if (time && la && inf->lstat.st_atime == nxt->lstat.st_atime && \
		inf->lstat.st_atim.tv_nsec < nxt->lstat.st_atim.tv_nsec)
		return (1);
	else if (time && la && inf->lstat.st_atime < nxt->lstat.st_atime)
		return (1);
	return (0);
}
#else

int	check_rev(t_fileinfo *inf, t_fileinfo *nxt, unsigned int bk)
{
	const unsigned int	time = ((bk >> TFLAG) & 1);
	const unsigned int	la = ((bk >> UFLAG) & 1);

	if (!time && ft_strcmp(inf->name, nxt->name) <= -1)
		return (1);
	else if (time && !la && inf->lstat.st_mtime == nxt->lstat.st_mtime && \
		inf->lstat.st_mtimespec.tv_nsec == nxt->lstat.st_mtimespec.tv_nsec && \
		ft_strcmp(inf->name, nxt->name) <= -1)
		return (1);
	else if (time && !la && inf->lstat.st_mtime == nxt->lstat.st_mtime && \
		inf->lstat.st_mtimespec.tv_nsec > nxt->lstat.st_mtimespec.tv_nsec)
		return (1);
	else if (time && !la && inf->lstat.st_mtime > nxt->lstat.st_mtime)
		return (1);
	else if (time && la && inf->lstat.st_atime == nxt->lstat.st_atime && \
		inf->lstat.st_atimespec.tv_nsec == nxt->lstat.st_atimespec.tv_nsec && \
		ft_strcmp(inf->name, nxt->name) <= -1)
		return (1);
	else if (time && la && inf->lstat.st_atime == nxt->lstat.st_atime && \
		inf->lstat.st_atimespec.tv_nsec > nxt->lstat.st_atimespec.tv_nsec)
		return (1);
	else if (time && la && inf->lstat.st_atime > nxt->lstat.st_atime)
		return (1);
	return (0);
}

int	check_norev(t_fileinfo *inf, t_fileinfo *nxt, unsigned int bk)
{
	const unsigned int	time = ((bk >> TFLAG) & 1);
	const unsigned int	la = ((bk >> UFLAG) & 1);

	if (!time && ft_strcmp(inf->name, nxt->name) >= 1)
		return (1);
	else if (time && !la && inf->lstat.st_mtime == nxt->lstat.st_mtime && \
		inf->lstat.st_mtimespec.tv_nsec == nxt->lstat.st_mtimespec.tv_nsec && \
		ft_strcmp(inf->name, nxt->name) >= 1)
		return (1);
	else if (time && !la && inf->lstat.st_mtime == nxt->lstat.st_mtime && \
		inf->lstat.st_mtimespec.tv_nsec < nxt->lstat.st_mtimespec.tv_nsec)
		return (1);
	else if (time && !la && inf->lstat.st_mtime < nxt->lstat.st_mtime)
		return (1);
	else if (time && la && inf->lstat.st_atime == nxt->lstat.st_atime && \
		inf->lstat.st_atimespec.tv_nsec == nxt->lstat.st_atimespec.tv_nsec && \
		ft_strcmp(inf->name, nxt->name) >= 1)
		return (1);
	else if (time && la && inf->lstat.st_atime == nxt->lstat.st_atime && \
		inf->lstat.st_atimespec.tv_nsec < nxt->lstat.st_atimespec.tv_nsec)
		return (1);
	else if (time && la && inf->lstat.st_atime < nxt->lstat.st_atime)
		return (1);
	return (0);
}
#endif
