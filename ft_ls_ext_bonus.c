/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_ext_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:29:40 by corellan          #+#    #+#             */
/*   Updated: 2024/05/21 11:14:11 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#ifdef __APPLE__

void	print_ext(t_fileinfo *info, char *ext_at)
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

void	process_ext(t_fileinfo *info, int *ret_err, char **ext_at)
{
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
		ft_del_mem((void **)ext_at, &free);
		return ;
	ft_del_mem((void **)ext_at, &free);
}
#else

void	process_ext(t_fileinfo *info, int *ret_err, char **ext_at)
{
	(*ext_at) = ft_calloc((info->ext_size + 1), sizeof(char));
	if (!(*ext_at))
	{
		(*ret_err) = -1;
		return ;
	}
	if (info->rel_path && \
		listxattr(info->rel_path, (*ext_at), info->ext_size) < 0)
	{
		ft_del_mem((void **)ext_at);
		return ;
	}
	else if (listxattr(info->name, (*ext_at), info->ext_size) < 0)
	{
		ft_del_mem((void **)ext_at);
		return ;
	}
}
#endif