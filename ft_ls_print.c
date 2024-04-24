/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:48:27 by corellan          #+#    #+#             */
/*   Updated: 2024/04/24 12:36:48 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_file(t_fileinfo *info, t_ls *ls)
{
	ft_bzero(ls->perm, sizeof(ls->perm));
	if (((ls->flags_info >> LFLAG) & 1))
	{
		info->pw = getpwuid(info->lstat.st_uid);
		info->gr = getgrgid(info->lstat.st_gid);
		store_attributes(info, ls);
		ft_printf("%s %*d ", ls->perm, ls->pad.pad_hl, info->lstat.st_nlink);
		if (info->pw)
			ft_printf("%-*s  ", ls->pad.pad_pw, info->pw->pw_name);
		else
			ft_printf("%-*u  ", ls->pad.pad_pw, info->lstat.st_uid);
		if (info->gr)
			ft_printf("%-*s  ", ls->pad.pad_gr, info->gr->gr_name);
		else
			ft_printf("%-*u  ", ls->pad.pad_gr, info->lstat.st_gid);
		ft_printf("%*s %s ", ls->pad.pad_size, info->file_size, info->time);
	}
	ft_printf("%s\n", info->name);
}

static void	files_error_loop(t_list *node, t_ls *ls, int error, t_lstls type)
{
	t_fileinfo	*info;

	info = node->content;
	if (type == DIRECTORY && ls->iter_lst == 0 && \
		((ls->flags_info >> LFLAG) & 1))
		ft_printf("total %d\n", ls->total_blocks);
	if (error == 1)
		ft_dprintf(2, "ft_ls: %s: %s\n", info->name, strerror(2));
	else if (type == ARGUMENT || ((ls->flags_info >> AFLAG) & 1) || \
		(!((ls->flags_info >> AFLAG) & 1) && info->name[0] != '.'))
		print_file(info, ls);
}

int	print_files_or_error(t_list **begin, t_ls *ls, int error, t_lstls type)
{
	t_list	*tmp;

	ls->iter_lst = 0;
	if (!begin || !(*begin))
		return (0);
	tmp = *begin;
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
		files_error_loop(tmp, ls, error, type);
		tmp = tmp->next;
		(ls->iter_lst)++;
	}
	return (0);
}
