/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_symlink.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:28:13 by corellan          #+#    #+#             */
/*   Updated: 2024/05/08 14:40:24 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	process_link(t_fileinfo **info, t_ls *ls, t_lstls type)
{
	ssize_t	rlink_return;
	int		st_status;

	rlink_return = 0;
	if (type == ARGUMENT)
		st_status = stat((*info)->name, &((*info)->stat));
	else if ((*info)->rel_path)
		st_status = stat((*info)->rel_path, &((*info)->stat));
	if (st_status == -1)
	{
		(*info)->er_lk = errno;
		return (0);
	}
	if (type == ARGUMENT)
		rlink_return = readlink((*info)->name, (*info)->lk, (PATH_MAX - 1));
	else if ((*info)->rel_path)
		rlink_return = readlink((*info)->rel_path, (*info)->lk, (PATH_MAX - 1));
	if (rlink_return)
	{
		(*info)->er_lk = errno;
		return (0);
	}
	if (S_ISDIR((*info)->stat.st_mode))
		(*info)->is_dir = 1;
	return (0);
}
