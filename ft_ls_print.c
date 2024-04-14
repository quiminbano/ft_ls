/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:43:14 by corellan          #+#    #+#             */
/*   Updated: 2024/04/14 17:39:12 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	store_permissions(t_fileinfo *info, t_ls *ls, size_t i)
{
	if ((i == 1 && (info->stat.st_mode & S_IRUSR)) || \
		(i == 4 && (info->stat.st_mode & S_IRGRP)) || \
		(i == 7 && (info->stat.st_mode & S_IROTH)))
		ls->permissions[i] = 'r';
	else if ((i == 2 && (info->stat.st_mode & S_IWUSR)) || \
		(i == 5 && (info->stat.st_mode & S_IWGRP)) || \
		(i == 8 && (info->stat.st_mode & S_IWOTH)))
		ls->permissions[i] = 'w';
	else if ((i == 3 && (info->stat.st_mode & S_IXUSR)) || \
		(i == 6 && (info->stat.st_mode & S_IXGRP)) || \
		(i == 9 && (info->stat.st_mode & S_IXOTH)))
		ls->permissions[i] = 'x';
	else
		ls->permissions[i] = '-';
}

static void	store_attributes(t_fileinfo *info, t_ls *ls)
{
	size_t	i;

	i = 1;
	if (S_ISBLK(info->stat.st_mode))
		ls->permissions[0] = 'b';
	else if (S_ISCHR(info->stat.st_mode))
		ls->permissions[0] = 'c';
	else if (S_ISDIR(info->stat.st_mode))
		ls->permissions[0] = 'd';
	else if (S_ISLNK(info->stat.st_mode))
		ls->permissions[0] = 'l';
	else if (S_ISSOCK(info->stat.st_mode))
		ls->permissions[0] = 's';
	else if (S_ISFIFO(info->stat.st_mode))
		ls->permissions[0] = 'p';
	else
		ls->permissions[0] = '-';
	while (i < 11)
	{
		store_permissions(info, ls, i);
		i++;
	}
}

static void	print_file(t_fileinfo *info, t_ls *ls)
{
	ft_bzero(ls->permissions, sizeof(ls->permissions));
	if (!((ls->flags_info >> AFLAG) & 1) && info->name[0] == '.')
		return ;
	if (((ls->flags_info >> AFLAG) & 1))
		store_attributes(info, ls);
}

void	print_files_or_error(t_list **begin, t_ls *ls, int error)
{
	t_list		*tmp;
	t_fileinfo	*info;

	if (!begin || !(*begin))
		return ;
	tmp = *begin;
	if (error == 1)
		ls->exit_status = 1;
	while (tmp)
	{
		info = tmp->content;
		if (error == 1)
			ft_dprintf(2, "ft_ls: %s: %s\n", info->name, strerror(2));
		else
			print_file(info, ls);
		tmp = tmp->next;
	}
}
