/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_paddings_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:16:18 by corellan          #+#    #+#             */
/*   Updated: 2024/05/22 17:08:36 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static const char	*get_year(const char *str)
{
	size_t	length;

	length = ft_strlen(str);
	if (length == 1)
		length = 0;
	else if (length > 1)
		length -= 2;
	while (length > 0 && ft_isdigit(str[length]))
		length--;
	return (str + length);
}

static void	get_correct_time(t_fileinfo *info, t_ls *ls, char **time)
{
	if (!((ls->flags_info >> UFLAG) & 1))
		(*time) = ctime(&(info->lstat.st_mtime));
	else
		(*time) = ctime(&(info->lstat.st_atime));
}

static int	get_time_string(t_fileinfo *info, t_ls *ls)
{
	time_t	time_nwd;
	char	*time_file;
	int		flag;

	time_nwd = time(NULL);
	flag = 0;
	get_correct_time(info, ls, &time_file);
	if ((info->lstat.st_mtime >= (time_nwd - SIX_MONTHS)) && \
		(info->lstat.st_mtime <= (time_nwd + SIX_MONTHS)))
		info->time = ft_substr(time_file, 4, 12);
	else
	{
		flag = 1;
		info->time = ft_substr(time_file, 4, 7);
	}
	if (!info->time)
		return (-1);
	if (flag == 1)
	{
		info->time = ft_strjoin_append(info->time, get_year(time_file), 5);
		if (!info->time)
			return (-1);
	}
	return (0);
}

static void	padding_user_and_group(t_fileinfo **info, t_ls *ls)
{
	size_t	length_us;
	size_t	length_gr;

	(*info)->pw = getpwuid((*info)->lstat.st_uid);
	(*info)->gr = getgrgid((*info)->lstat.st_gid);
	if ((*info)->pw)
		length_us = ft_strlen((*info)->pw->pw_name);
	else
		length_us = ft_numlength_base((*info)->lstat.st_uid, 10);
	if (length_us > ls->pad.pad_pw)
		ls->pad.pad_pw = length_us;
	if ((*info)->gr)
		length_gr = ft_strlen((*info)->gr->gr_name);
	else
		length_gr = ft_numlength_base((*info)->lstat.st_gid, 10);
	if (length_gr > ls->pad.pad_gr)
		ls->pad.pad_gr = length_gr;
}

int	calculate_paddings(t_list **begin, t_ls *ls, t_lstls type)
{
	t_list		*tmp;
	t_fileinfo	*info;

	tmp = *begin;
	ls->total_blocks = 0;
	while (tmp)
	{
		info = tmp->content;
		if ((type == ARGUMENT) || ((ls->flags_info >> AFLAG) & 1) || \
			(!((ls->flags_info >> AFLAG) & 1) && info->name[0] != '.'))
		{
			ls->len_link = ft_numlength_base(info->lstat.st_nlink, 10);
			if (ls->len_link > ls->pad.pad_hl)
				ls->pad.pad_hl = ls->len_link;
			padding_user_and_group(&info, ls);
			if (get_time_string(info, ls) == -1)
				return (-1);
			padding_file_size(info, ls);
			ls->total_blocks += info->lstat.st_blocks;
		}
		tmp = tmp->next;
	}
	return (0);
}
