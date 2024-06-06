/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_ext_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:18:05 by corellan          #+#    #+#             */
/*   Updated: 2024/06/06 12:27:35 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#ifdef __APPLE__

static void	print_ext(t_fileinfo *info, char *ext_at)
{
	ssize_t	return_bytes;
	size_t	index;
	char	*path;
	char	*name;

	index = 0;
	path = info->name;
	if (info->rel_path)
		path = info->rel_path;
	name = ext_at;
	while (index < info->ext_size)
	{
		return_bytes = getxattr(path, name, NULL, 0, 0, 0);
		ft_printf("\t%s\t%*d\n", name, \
			(ft_numlength_base(return_bytes, 10) + 7), (int)return_bytes);
		index = (ft_strlen(name) + 1);
		name += index;
	}
}

static void	process_ext(t_fileinfo *info, int *ret_err, char **ext_at)
{
	if (!info->ext_size)
		return ;
	(*ext_at) = ft_calloc((info->ext_size + 1), sizeof(char));
	if (!(*ext_at))
	{
		(*ret_err) = -1;
		return ;
	}
	if (info->rel_path && \
		listxattr(info->rel_path, (*ext_at), info->ext_size, 0) > 0)
		return ;
	else if (listxattr(info->name, (*ext_at), info->ext_size, 0) > 0)
		return ;
	ft_del_mem((void **)ext_at);
}
#else

static void	print_ext(t_fileinfo *info, char *ext_at)
{
	ssize_t	return_bytes;
	size_t	index;
	size_t	length;
	char	*path;
	char	*name;

	index = 0;
	length = 0;
	path = info->name;
	if (info->rel_path)
		path = info->rel_path;
	name = ext_at;
	while (index < info->ext_size)
	{
		return_bytes = getxattr(path, name, NULL, 0);
		if (return_bytes == -1)
			return ;
		ft_printf("\t%s\t%*d\n", name, \
			(ft_numlength_base(return_bytes, 10) + 7), (int)return_bytes);
		length = (ft_strlen(name) + 1);
		name += length;
		index += length;
	}
}

static void	process_ext(t_fileinfo *info, int *ret_err, char **ext_at)
{
	if (!info->ext_size)
		return ;
	(*ext_at) = ft_calloc((info->ext_size + 1), sizeof(char));
	if (!(*ext_at))
	{
		(*ret_err) = -1;
		return ;
	}
	if (info->rel_path && \
		listxattr(info->rel_path, (*ext_at), info->ext_size) > 0)
		return ;
	else if (listxattr(info->name, (*ext_at), info->ext_size) > 0)
		return ;
	ft_del_mem((void **)ext_at);
}
#endif

void	print_ext_attr(t_fileinfo *info, t_ls *ls, int *ret_err)
{
	char	*ext_at;

	ext_at = NULL;
	if (((ls->flags_info >> ATFLAG) & 1))
		process_ext(info, ret_err, &ext_at);
	if ((*ret_err) == -1)
		return ;
	if (ext_at)
		print_ext(info, ext_at);
	ft_del_mem((void **)(&ext_at));
}
