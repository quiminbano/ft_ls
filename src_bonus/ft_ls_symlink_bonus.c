/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_symlink_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:28:13 by corellan          #+#    #+#             */
/*   Updated: 2024/06/19 17:06:47 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

void	process_link(t_fileinfo **info, t_lstls type, t_ls *ls)
{
	if (type == ARGUMENT)
		stat((*info)->name, &((*info)->stat));
	else if ((*info)->rel_path)
		stat((*info)->rel_path, &((*info)->stat));
	if (S_ISDIR((*info)->stat.st_mode) && !((ls->flags_info >> LFLAG) & 1))
		(*info)->is_dir = 1;
}
