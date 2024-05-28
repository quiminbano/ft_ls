/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:48:27 by corellan          #+#    #+#             */
/*   Updated: 2024/05/28 18:35:00 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static void	print_filename(t_fileinfo *info, t_ls *ls)
{
	handle_colors(info, ls, info->lstat.st_mode);
	ft_printf("%s%s%s", info->color, info->name, info->end);
	if (((ls->flags_info >> LFLAG) & 1) && (S_ISLNK(info->lstat.st_mode)))
		ft_printf(" -> %s", info->lk);
	ft_printf("\n");
}

#ifdef __APPLE__

static void	print_filedata(t_fileinfo *info, t_ls *ls, int *ret_err)
{
	ft_bzero(ls->perm, sizeof(ls->perm));
	if (((ls->flags_info >> LFLAG) & 1))
	{
		info->pw = getpwuid(info->lstat.st_uid);
		info->gr = getgrgid(info->lstat.st_gid);
		store_attributes(info, ls);
		ft_printf("%s %*d ", ls->perm, ls->pad.pad_hl, info->lstat.st_nlink);
		if (info->pw && !((ls->flags_info >> GFLAG) & 1))
			ft_printf("%-*s  ", ls->pad.pad_pw, info->pw->pw_name);
		else if (!((ls->flags_info >> GFLAG) & 1))
			ft_printf("%-*u  ", ls->pad.pad_pw, info->lstat.st_uid);
		if (info->gr)
			ft_printf("%-*s  ", ls->pad.pad_gr, info->gr->gr_name);
		else
			ft_printf("%-*u  ", ls->pad.pad_gr, info->lstat.st_gid);
		check_special_files(info, ls);
		ft_printf("%s ", info->time);
	}
	print_filename(info, ls);
	if (((ls->flags_info >> EFLAG) & 1) || ((ls->flags_info >> ATFLAG) & 1))
		print_ext_acl(info, ls, ret_err);
}
#else

static void	print_filedata(t_fileinfo *info, t_ls *ls, int *ret_err)
{
	ft_bzero(ls->perm, sizeof(ls->perm));
	if (((ls->flags_info >> LFLAG) & 1))
	{
		info->pw = getpwuid(info->lstat.st_uid);
		info->gr = getgrgid(info->lstat.st_gid);
		store_attributes(info, ls);
		ft_printf("%s %*d ", ls->perm, ls->pad.pad_hl, info->lstat.st_nlink);
		if (info->pw && !((ls->flags_info >> GFLAG) & 1))
			ft_printf("%-*s  ", ls->pad.pad_pw, info->pw->pw_name);
		else if (!((ls->flags_info >> GFLAG) & 1))
			ft_printf("%-*u  ", ls->pad.pad_pw, info->lstat.st_uid);
		if (info->gr && !((ls->flags_info >> GEEFLAG) & 1))
			ft_printf("%-*s  ", ls->pad.pad_gr, info->gr->gr_name);
		else if (!((ls->flags_info >> GEEFLAG) & 1))
			ft_printf("%-*s  ", ls->pad.pad_gr, info->gr->gr_name);
		else
			ft_printf("%-*u  ", ls->pad.pad_gr, info->lstat.st_gid);
		check_special_files(info, ls);
		ft_printf("%s ", info->time);
	}
	print_filename(info, ls);
	if (((ls->flags_info >> EFLAG) & 1) || ((ls->flags_info >> ATFLAG) & 1))
		print_ext_acl(info, ls, ret_err);
}
#endif

static int	files_error_loop(t_list *node, t_ls *ls, int error, t_lstls type)
{
	t_fileinfo	*info;
	int			ret_err;

	info = node->content;
	ret_err = 0;
	if (type == DIRECTORY && ls->iter_lst == 0 && \
		((ls->flags_info >> LFLAG) & 1))
		ft_printf("total %d\n", ls->total_blocks);
	if (error == 1)
	{
		if (info->er_st)
			ft_dprintf(2, "ft_ls: %s: %s\n", info->name, strerror(info->er_st));
		else if (info->er_lk)
			ft_dprintf(2, "ft_ls: %s: %s\n", info->name, strerror(info->er_lk));
	}
	else if (type == ARGUMENT || ((ls->flags_info >> AFLAG) & 1) || \
		(!((ls->flags_info >> AFLAG) & 1) && info->name[0] != '.'))
		print_filedata(info, ls, &ret_err);
	if (ret_err == -1)
		return (-1);
	return (0);
}

int	print_files_or_error(t_list **begin, t_ls *ls, int error, t_lstls type)
{
	t_list	*tmp;

	if (!begin || !(*begin))
		return (0);
	tmp = *begin;
	ls->iter_lst = 1;
	if ((type == ARGUMENT) || ((ls->flags_info >> AFLAG) & 1) || \
		ft_lstsize(tmp) > 2)
		ls->iter_lst = 0;
	if (error == 1)
		ls->exit_status = 1;
	else if (tmp && ((ls->flags_info >> LFLAG) & 1))
	{
		ft_bzero(&(ls->pad), sizeof(ls->pad));
		if (calculate_paddings(begin, ls, type) == -1)
			return (-1);
	}
	while (tmp)
	{
		if (files_error_loop(tmp, ls, error, type) == -1)
			return (-1);
		tmp = tmp->next;
		(ls->iter_lst)++;
	}
	return (0);
}
