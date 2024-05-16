/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_symlink_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:28:13 by corellan          #+#    #+#             */
/*   Updated: 2024/05/16 14:03:57 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

void	process_link(t_fileinfo **info, t_lstls type, t_ls *ls)
{
	ssize_t	rlink_return;

	rlink_return = 0;
	if (type == ARGUMENT)
		stat((*info)->name, &((*info)->stat));
	else if ((*info)->rel_path)
		stat((*info)->rel_path, &((*info)->stat));
	if (type == ARGUMENT)
		rlink_return = readlink((*info)->name, (*info)->lk, (PATH_MAX - 1));
	else if ((*info)->rel_path)
		rlink_return = readlink((*info)->rel_path, (*info)->lk, (PATH_MAX - 1));
	if (rlink_return == -1)
	{
		(*info)->er_lk = errno;
		return ;
	}
	if (S_ISDIR((*info)->stat.st_mode) && !((ls->flags_info >> LFLAG) & 1))
		(*info)->is_dir = 1;
}
