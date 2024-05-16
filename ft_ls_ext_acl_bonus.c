/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_ext_acl_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:18:05 by corellan          #+#    #+#             */
/*   Updated: 2024/05/16 18:52:51 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#ifdef __APPLE__

static void	process_acl(t_fileinfo *info, int *ret_err, char **acl_at)
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

static void	process_ext(t_fileinfo *info, int *ret_err, char **ext_at)
{
	(*ext_at) = ft_calloc((info->ext_size + 1), sizeof(char));
	if (!(*ext_at))
	{
		(*ret_err) = -1;
		return ;
	}
	if (info->rel_path && \
		listxattr(info->rel_path, (*ext_at), info->ext_size, 0) < 0)
	{
		ft_del_mem((void **)ext_at);
		return ;
	}
	else if (listxattr(info->name, (*ext_at), info->ext_size, 0) < 0)
	{
		ft_del_mem((void **)ext_at);
		return ;
	}
}
#else

static void	process_acl(t_fileinfo *info, int *ret_err, char **acl_at)
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

static void	process_ext(t_fileinfo *info, int *ret_err, char **ext_at)
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

void	print_ext_acl(t_fileinfo *info, t_ls *ls, int *ret_err)
{
	char	*ext_at;
	char	*acl_at;

	ext_at = NULL;
	acl_at = NULL;
	if (((ls->flags_info >> ATFLAG) & 1))
		process_ext(info, ret_err, &ext_at);
	if ((*ret_err) == -1)
		return ;
	if (((ls->flags_info >> EFLAG) & 1))
		process_acl(info, ret_err, &acl_at);
	if ((*ret_err) == -1)
	{
		ft_del_mem((void **)(&ext_at));
		return ;
	}
	if (ext_at)
		ft_printf("%s\n", ext_at);
	if (acl_at)
		ft_printf("%s\n", ext_at);
	ft_del_mem((void **)(&ext_at));
	ft_del_mem((void **)(&acl_at));
}
