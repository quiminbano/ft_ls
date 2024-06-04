/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_colors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:01:19 by corellan          #+#    #+#             */
/*   Updated: 2024/06/04 11:58:44 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#ifdef __APPLE__

static void	set_colors(t_fileinfo *info, t_ls *ls, mode_t mode)
{
	if (!((ls->flags_info >> GEEFLAG) & 1) || !isatty(STDOUT_FILENO))
		return ;
	if (S_ISDIR(mode) && (S_IWOTH & mode) && (S_ISVTX & mode))
		info->color = STKCOL;
	else if (S_ISDIR(mode) && (S_IWOTH & mode) && !(S_ISVTX & mode))
		info->color = WSTKCOL;
	else if (S_ISDIR(mode))
		info->color = DIRCOL;
	else if (S_ISLNK(mode))
		info->color = SYMCOL;
	else if (S_ISSOCK(mode))
		info->color = SOCKCOL;
	else if (S_ISFIFO(mode))
		info->color = PIPECOL;
	else if (S_ISBLK(mode))
		info->color = BLKCOL;
	else if (S_ISCHR(mode))
		info->color = CHRCOL;
	else if ((S_IXUSR & mode) && (S_ISUID & mode))
		info->color = XUIDCOL;
	else if ((S_IXGRP & mode) && (S_ISGID & mode))
		info->color = XGIDCOL;
	else if ((S_IXUSR & mode) || (S_IXGRP & mode) || (S_IXOTH & mode))
		info->color = EXECCOL;
}
#else

static void	set_colors(t_fileinfo *info, t_ls *ls, mode_t mode)
{
	if (!((ls->flags_info >> GEEFLAG) & 1) || !isatty(STDOUT_FILENO))
		return ;
	if (S_ISDIR(mode) && (S_IWOTH & mode) && (S_ISVTX & mode))
		info->color = STKCOL;
	else if (S_ISDIR(mode) && (S_IWOTH & mode) && !(S_ISVTX & mode))
		info->color = WSTKCOL;
	else if (S_ISDIR(mode))
		info->color = DIRCOL;
	else if (S_ISLNK(mode))
		info->color = SYMCOL;
	else if (__S_ISTYPE(mode, __S_IFSOCK))
		info->color = SOCKCOL;
	else if (S_ISFIFO(mode))
		info->color = PIPECOL;
	else if (S_ISBLK(mode))
		info->color = BLKCOL;
	else if (S_ISCHR(mode))
		info->color = CHRCOL;
	else if ((S_IXUSR & mode) && (S_ISUID & mode))
		info->color = XUIDCOL;
	else if ((S_IXGRP & mode) && (S_ISGID & mode))
		info->color = XGIDCOL;
	else if ((S_IXUSR & mode) || (S_IXGRP & mode) || (S_IXOTH & mode))
		info->color = EXECCOL;
}
#endif

void	handle_colors(t_fileinfo *info, t_ls *ls, mode_t mode)
{
	info->color = ls->empty;
	info->end = ls->empty;
	set_colors(info, ls, mode);
	if (ft_strcmp(info->color, ""))
		info->end = RESET;
}
