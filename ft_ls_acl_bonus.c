/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_acl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:31:43 by corellan          #+#    #+#             */
/*   Updated: 2024/06/02 00:40:07 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#ifdef __APPLE__

static char	**split_acl(char *acl_at)
{
	char	**temp_split;
	char	*temp_arr;

	temp_split = ft_split(acl_at, '\n');
	if (!temp_split)
		return (NULL);
	if (ft_split_length(temp_split) < 2)
	{
		ft_free_split(temp_split);
		temp_split = NULL;
		return (NULL);
	}
	temp_arr = ft_strdup(temp_split[1]);
	if (!temp_arr)
	{
		ft_free_split(temp_split);
		temp_split = NULL;
		return (NULL);
	}
	ft_free_split(temp_split);
	temp_split = NULL;
	temp_split = ft_split(temp_arr, ':');
	ft_del_mem((void **)(&temp_arr));
	return (temp_split);
}

void	print_acl(int *ret_err, char **acl_at)
{
	char	**temp_split;

	temp_split = split_acl((*acl_at));
	if (!temp_split)
	{
		(*ret_err) = -1;
		return ;
	}
	if (ft_split_length(temp_split) < 6)
	{
		ft_free_split(temp_split);
		temp_split = NULL;
		ft_printf(" 0: acl incomplete\n");
		return ;
	}
	ft_printf(" 0: group:%s %s %s\n", temp_split[2], temp_split[4], \
		temp_split[5]);
	ft_free_split(temp_split);
	temp_split = NULL;
}

void	process_acl(t_fileinfo *info, int *ret_err, char **acl_at)
{
	if (info->acl_usage != 1)
		return ;
	(*acl_at) = acl_to_text(info->acl, &(info->acl_size));
	if (!(*acl_at))
	{
		(*ret_err) = -1;
		return ;
	}
}
#else

void	process_acl(t_fileinfo *info, int *ret_err, char **acl_at)
{
	if (info->acl_size <= 0)
		return ;
	if (!info->ext_size)
		return ;
	(*acl_at) = ft_calloc((info->ext_size + 1), sizeof(char));
	if (!(*acl_at))
	{
		(*ret_err) = -1;
		return ;
	}
	if (info->rel_path && \
		listxattr(info->rel_path, (*acl_at), (size_t)info->acl_size) > 0)
		return ;
	else if (listxattr(info->name, (*acl_at), (size_t)info->acl_size) > 0)
		return ;
	ft_del_mem((void **)acl_at);
}

void	print_acl(t_fileinfo *info, char *acl_at)
{
	ssize_t	return_bytes;
	size_t	index;
	char	*path;
	char	*name;

	index = 0;
	path = info->name;
	if (info->rel_path)
		path = info->rel_path;
	name = acl_at;
	while (index < info->ext_size)
	{
		return_bytes = getxattr(path, name, NULL, 0);
		ft_printf("\t%s\t%*d\n", name, \
			(ft_numlength_base(return_bytes, 10) + 7), (int)return_bytes);
		index = (ft_strlen(name) + 1);
		name += index;
	}
}
#endif
