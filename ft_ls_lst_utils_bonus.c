/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_lst_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 09:07:41 by corellan          #+#    #+#             */
/*   Updated: 2024/05/21 11:27:38 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

void	delete_fileinfo(void *fileinfo)
{
	t_fileinfo	*ptr;

	ptr = (t_fileinfo *)fileinfo;
	if (!ptr)
		return ;
	if (ptr->name)
		ft_del_mem((void **)(&ptr->name), &free);
	ft_bzero(&(ptr->stat), sizeof(ptr->stat));
	ft_bzero(&(ptr->lstat), sizeof(ptr->lstat));
	if (ptr->time)
		ft_del_mem((void **)(&ptr->time), &free);
	if (ptr->file_size)
		ft_del_mem((void **)(&ptr->file_size), &free);
	if (ptr->rel_path)
		ft_del_mem((void **)(&ptr->rel_path), &free);
	if (ptr->acl)
		ft_del_mem((void **)(&ptr->acl), &acl_free);
	ft_del_mem((void **)(&ptr), &free);
	fileinfo = NULL;
}

int	free_lst(t_list **dir, t_list **file, t_list **err)
{
	if (dir && *dir)
		ft_lstclear(&(*dir), &delete_fileinfo);
	if (file && *file)
		ft_lstclear(&(*file), &delete_fileinfo);
	if (err && *err)
		ft_lstclear(&(*err), &delete_fileinfo);
	return (-1);
}
