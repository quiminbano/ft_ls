/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_acl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:31:43 by corellan          #+#    #+#             */
/*   Updated: 2024/05/17 16:37:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#ifdef __APPLE__

void	process_acl(t_fileinfo *info, int *ret_err, char **acl_at)
{
	(*acl_at) = ft_calloc((info->acl_size + 1), sizeof(char));
	if (!(*acl_at))
	{
		(*ret_err) = -1;
		return ;
	}
	if (info->rel_path && \
		getxattr(info->rel_path, "system.acl", \
		(*acl_at), info->acl_size, 0, 0) < 0)
	{
		ft_del_mem((void **)acl_at);
		return ;
	}
	else if (getxattr(info->rel_path, "system.acl", \
		(*acl_at), info->acl_size, 0, 0) < 0)
	{
		ft_del_mem((void **)acl_at);
		return ;
	}
}
#else

void	process_acl(t_fileinfo *info, int *ret_err, char **acl_at)
{
	(*acl_at) = ft_calloc((info->acl_size + 1), sizeof(char));
	if (!(*acl_at))
	{
		(*ret_err) = -1;
		return ;
	}
	if (info->rel_path && \
		getxattr(info->rel_path, "system.acl", \
		(*acl_at), info->acl_size) < 0)
	{
		ft_del_mem(acl_at);
		return ;
	}
	else if (getxattr(info->rel_path, "system.acl", \
		(*acl_at), info->acl_size) < 0)
	{
		ft_del_mem(acl_at);
		return ;
	}
}
#endif