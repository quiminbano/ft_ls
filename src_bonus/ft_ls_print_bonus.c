/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:48:27 by corellan          #+#    #+#             */
/*   Updated: 2024/06/19 17:24:25 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static void	print_filename(t_fileinfo *info, t_ls *ls)
{
	handle_colors(info, ls, info->lstat.st_mode);
	ft_printf("%s%s%s", info->color, info->name, info->end);
	if (((ls->flags_info >> LFLAG) & 1) && (S_ISLNK(info->lstat.st_mode) && \
		info->print_lk))
		ft_printf(" -> %s", info->lk);
	ft_printf("\n");
}

static void	check_lnk_store_attr(t_fileinfo *info, t_ls *ls)
{
	ssize_t	readlink_status;
	char	*path;

	readlink_status = 0;
	info->print_lk = 0;
	store_attributes(info, ls);
	if (!S_ISLNK(info->lstat.st_mode))
		return ;
	ft_bzero((info->lk), sizeof(info->lk));
	path = info->name;
	if (info->rel_path)
		path = info->rel_path;
	readlink_status = readlink(path, info->lk, (PATH_MAX - 1));
	if (readlink_status == -1)
	{
		ft_dprintf(2, "\nft_ls: %s: %s\n", path, strerror(errno));
		return ;
	}
	info->print_lk = 1;
}

static void	print_filedata(t_fileinfo *info, t_ls *ls, int *ret_err)
{
	if (((ls->flags_info >> LFLAG) & 1))
	{
		info->pw = getpwuid(info->lstat.st_uid);
		info->gr = getgrgid(info->lstat.st_gid);
		if (errno == ENOMEM)
		{
			(*ret_err) = -1;
			return ;
		}
		check_lnk_store_attr(info, ls);
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
	if (((ls->flags_info >> ATFLAG) & 1))
		print_ext_attr(info, ls, ret_err);
}

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
	}
	else if (type == ARGUMENT || ((ls->flags_info >> AFLAG) & 1) || \
		(!((ls->flags_info >> AFLAG) & 1) && info->name[0] != '.'))
	{
		ft_bzero(ls->perm, sizeof(ls->perm));
		print_filedata(info, ls, &ret_err);
	}
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
