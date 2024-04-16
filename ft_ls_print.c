/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:48:27 by corellan          #+#    #+#             */
/*   Updated: 2024/04/16 07:30:59 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_file(t_fileinfo *info, t_ls *ls)
{
	ft_bzero(ls->permissions, sizeof(ls->permissions));
	if (!((ls->flags_info >> AFLAG) & 1) && info->name[0] == '.')
		return ;
	if (((ls->flags_info >> AFLAG) & 1))
		store_attributes(info, ls);
}

void	print_files_or_error(t_list **begin, t_ls *ls, int error)
{
	t_list		*tmp;
	t_fileinfo	*info;

	if (!begin || !(*begin))
		return ;
	tmp = *begin;
	if (error == 1)
		ls->exit_status = 1;
	else if (tmp)
		calculate_paddings();
	while (tmp)
	{
		info = tmp->content;
		if (error == 1)
			ft_dprintf(2, "ft_ls: %s: %s\n", info->name, strerror(2));
		else
			print_file(info, ls);
		tmp = tmp->next;
	}
}
