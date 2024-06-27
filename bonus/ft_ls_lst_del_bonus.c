/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_lst_del_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:02:43 by corellan          #+#    #+#             */
/*   Updated: 2024/06/03 14:29:05 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#ifdef __APPLE__

void	delete_fileinfo(void *fileinfo)
{
	t_fileinfo	*ptr;

	ptr = (t_fileinfo *)fileinfo;
	if (!ptr)
		return ;
	if (ptr->name)
		ft_del_mem((void **)(&ptr->name));
	ft_bzero(&(ptr->stat), sizeof(ptr->stat));
	ft_bzero(&(ptr->lstat), sizeof(ptr->lstat));
	if (ptr->time)
		ft_del_mem((void **)(&ptr->time));
	if (ptr->file_size)
		ft_del_mem((void **)(&ptr->file_size));
	if (ptr->rel_path)
		ft_del_mem((void **)(&ptr->rel_path));
	if (ptr->acl)
		acl_free(ptr->acl);
	ptr->acl = NULL;
	ft_del_mem((void **)(&ptr));
	fileinfo = NULL;
}
#else

void	delete_fileinfo(void *fileinfo)
{
	t_fileinfo	*ptr;

	ptr = (t_fileinfo *)fileinfo;
	if (!ptr)
		return ;
	if (ptr->name)
		ft_del_mem((void **)(&ptr->name));
	ft_bzero(&(ptr->stat), sizeof(ptr->stat));
	ft_bzero(&(ptr->lstat), sizeof(ptr->lstat));
	if (ptr->time)
		ft_del_mem((void **)(&ptr->time));
	if (ptr->file_size)
		ft_del_mem((void **)(&ptr->file_size));
	if (ptr->rel_path)
		ft_del_mem((void **)(&ptr->rel_path));
	ft_del_mem((void **)(&ptr));
	fileinfo = NULL;
}
#endif
