/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:43:14 by corellan          #+#    #+#             */
/*   Updated: 2024/04/15 12:55:31 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	store_permissions(t_fileinfo *info, t_ls *ls, size_t i)
{
	if ((i == 1 && (info->lstat.st_mode & S_IRUSR)) || \
		(i == 4 && (info->lstat.st_mode & S_IRGRP)) || \
		(i == 7 && (info->lstat.st_mode & S_IROTH)))
		ls->permissions[i] = 'r';
	else if ((i == 2 && (info->lstat.st_mode & S_IWUSR)) || \
		(i == 5 && (info->lstat.st_mode & S_IWGRP)) || \
		(i == 8 && (info->lstat.st_mode & S_IWOTH)))
		ls->permissions[i] = 'w';
	else if ((i == 3 && (info->lstat.st_mode & S_IXUSR)) || \
		(i == 6 && (info->lstat.st_mode & S_IXGRP)) || \
		(i == 9 && (info->lstat.st_mode & S_IXOTH)))
		ls->permissions[i] = 'x';
	else
		ls->permissions[i] = '-';
}

#ifdef __APPLE__

void	store_attributes(t_fileinfo *info, t_ls *ls)
{
	size_t	i;

	i = 0;
	if (S_ISBLK(info->lstat.st_mode))
		ls->permissions[0] = 'b';
	else if (S_ISCHR(info->lstat.st_mode))
		ls->permissions[0] = 'c';
	else if (S_ISDIR(info->lstat.st_mode))
		ls->permissions[0] = 'd';
	else if (S_ISLNK(info->lstat.st_mode))
		ls->permissions[0] = 'l';
	else if (S_ISSOCK(info->lstat.st_mode))
		ls->permissions[0] = 's';
	else if (S_ISFIFO(info->lstat.st_mode))
		ls->permissions[0] = 'p';
	else
		ls->permissions[0] = '-';
	while (++i < 11)
		store_permissions(info, ls, i);
	if (listxattr(info->name, NULL, 0, 0) < 0)
		ls->permissions[i] = ' ';
	else
		ls->permissions[i] = '@';
}
#else

void	store_attributes(t_fileinfo *info, t_ls *ls)
{
	size_t	i;

	i = 0;
	if (S_ISBLK(info->lstat.st_mode))
		ls->permissions[0] = 'b';
	else if (S_ISCHR(info->lstat.st_mode))
		ls->permissions[0] = 'c';
	else if (S_ISDIR(info->lstat.st_mode))
		ls->permissions[0] = 'd';
	else if (S_ISLNK(info->lstat.st_mode))
		ls->permissions[0] = 'l';
	else if (S_ISSOCK(info->lstat.st_mode))
		ls->permissions[0] = 's';
	else if (S_ISFIFO(info->lstat.st_mode))
		ls->permissions[0] = 'p';
	else
		ls->permissions[0] = '-';
	while (++i < 11)
		store_permissions(info, ls, i);
	if (listxattr(info->name, NULL, 0) < 0)
		ls->permissions[i] = ' ';
	else
		ls->permissions[i] = '@';
}
#endif
