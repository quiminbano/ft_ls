/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_ext_acl_interface_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:18:05 by corellan          #+#    #+#             */
/*   Updated: 2024/06/02 00:48:21 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#ifdef __APPLE__

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
		print_ext(info, ext_at);
	if (acl_at)
		print_acl(ret_err, &acl_at);
	ft_del_mem((void **)(&ext_at));
	if (acl_at)
		acl_free(acl_at);
	acl_at = NULL;
}
#else

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
		print_ext(info, ext_at);
	if (acl_at)
		print_acl(info, acl_at);
	ft_del_mem((void **)(&ext_at));
	ft_del_mem((void **)(&acl_at));
}
#endif
