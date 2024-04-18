/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_paddings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:16:18 by corellan          #+#    #+#             */
/*   Updated: 2024/04/18 08:24:33 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

static int	get_time_string(t_fileinfo *info)
{
	time_t	time_nwd;
	char	*current_time;
	char	*time_file;
	int		flag;

	time_nwd = time(NULL);
	flag = 0;
	current_time = ctime(&time_nwd);
	time_file = ctime(&(info->lstat.st_mtime));
	if (!ft_strcmp(get_year(current_time), get_year(time_file)))
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

static void	padding_user_and_group(t_fileinfo *info, t_ls *ls)
{
	size_t	length_us;
	size_t	length_gr;

	if (info->pw)
		length_us = ft_strlen(info->pw->pw_name);
	else
		length_us = ft_numlength_base(info->lstat.st_uid, 10);
	if (length_us > ls->pad.pad_pw)
		ls->pad.pad_pw = length_us;
	if (info->gr)
		length_gr = ft_strlen(info->gr->gr_name);
	else
		length_gr = ft_numlength_base(info->lstat.st_gid, 10);
	if (length_gr > ls->pad.pad_gr)
		ls->pad.pad_gr = length_gr;
}

int	calculate_paddings(t_list **begin, t_ls *ls)
{
	t_list		*tmp;
	t_fileinfo	*info;
	size_t		length_links;
	size_t		length_size;

	tmp = *begin;
	ft_bzero(&(ls->pad), sizeof(ls->pad));
	while (tmp)
	{
		info = tmp->content;
		length_links = ft_numlength_base(info->lstat.st_nlink, 10);
		if (length_links > ls->pad.pad_hl)
			ls->pad.pad_hl = length_links;
		padding_user_and_group(info, ls);
		if (get_time_string(info) == -1)
			return (-1);
		length_size = ft_strlen(info->file_size);
		if (length_size > ls->pad.pad_size)
			ls->pad.pad_size = length_size;
		ls->total_blocks += info->lstat.st_blocks;
		tmp = tmp->next;
	}
	return (0);
}
