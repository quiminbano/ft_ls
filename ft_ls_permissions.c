/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:43:14 by corellan          #+#    #+#             */
/*   Updated: 2024/05/16 11:50:57 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	store_perm(t_fileinfo *info, t_ls *ls, size_t i)
{
	const mode_t	mode = info->lstat.st_mode;

	if ((i == 1 && (mode & S_IRUSR)) || (i == 4 && (mode & S_IRGRP)) || \
		(i == 7 && (mode & S_IROTH)))
		ls->perm[i] = 'r';
	else if ((i == 2 && (mode & S_IWUSR)) || (i == 5 && (mode & S_IWGRP)) || \
		(i == 8 && (mode & S_IWOTH)))
		ls->perm[i] = 'w';
	else if ((i == 3 && !(mode & S_IXUSR) && (mode & S_ISUID)) || \
		(i == 6 && !(mode & S_IXGRP) && (mode & S_ISGID)))
		ls->perm[i] = 'S';
	else if ((i == 3 && (mode & S_IXUSR) && (mode & S_ISUID)) || \
		(i == 6 && (mode & S_IXGRP) && (mode & S_ISGID)))
		ls->perm[i] = 's';
	else if ((i == 9 && !(mode & S_IXOTH) && (mode & S_ISVTX)))
		ls->perm[i] = 'T';
	else if ((i == 9 && (mode & S_IXOTH) && (mode & S_ISVTX)))
		ls->perm[i] = 't';
	else if ((i == 3 && (mode & S_IXUSR)) || (i == 6 && (mode & S_IXGRP)) || \
		(i == 9 && (mode & S_IXOTH)))
		ls->perm[i] = 'x';
	else
		ls->perm[i] = '-';
}

void	store_attributes(t_fileinfo *info, t_ls *ls)
{
	size_t	i;

	i = 0;
	if (S_ISBLK(info->lstat.st_mode))
		ls->perm[0] = 'b';
	else if (S_ISCHR(info->lstat.st_mode))
		ls->perm[0] = 'c';
	else if (S_ISDIR(info->lstat.st_mode))
		ls->perm[0] = 'd';
	else if (S_ISLNK(info->lstat.st_mode))
		ls->perm[0] = 'l';
	else if (S_ISSOCK(info->lstat.st_mode))
		ls->perm[0] = 's';
	else if (S_ISFIFO(info->lstat.st_mode))
		ls->perm[0] = 'p';
	else
		ls->perm[0] = '-';
	while (++i < 10)
		store_perm(info, ls, i);
	ls->perm[i] = ' ';
}
