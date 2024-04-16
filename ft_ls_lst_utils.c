/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 09:07:41 by corellan          #+#    #+#             */
/*   Updated: 2024/04/16 22:10:52 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap_pointers(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	delete_fileinfo(void *fileinfo)
{
	t_fileinfo	*ptr;

	ptr = (t_fileinfo *)fileinfo;
	if (!ptr)
		return ;
	if (ptr->name)
		free(ptr->name);
	ptr->name = NULL;
	ft_bzero(&(ptr->stat), sizeof(ptr->stat));
	ft_bzero(&(ptr->lstat), sizeof(ptr->lstat));
	if (ptr->time)
		free(ptr->time);
	ptr->time = NULL;
	if (ptr->file_size)
		free(ptr->file_size);
	ptr->file_size = NULL;
	free(ptr);
	ptr = NULL;
	fileinfo = NULL;
}

void	free_lst(t_list *dir, t_list *file, t_list *err)
{
	if (dir)
		ft_lstclear(&dir, &delete_fileinfo);
	if (file)
		ft_lstclear(&file, &delete_fileinfo);
	if (err)
		ft_lstclear(&err, &delete_fileinfo);
}
