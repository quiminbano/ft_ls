/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:43:14 by corellan          #+#    #+#             */
/*   Updated: 2024/04/13 22:52:37 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(t_list **begin, t_ls *ls)
{
	t_list		*tmp;
	t_fileinfo	*info;

	tmp = *begin;
	while (tmp)
	{
		ls->exit_status = 1;
		info = tmp->content;
		ft_dprintf(2, "ft_ls: %s: %s\n", info->name, strerror(2));
		tmp = tmp->next;
	}
}

int	print_files(t_list **begin, t_ls *ls)
{
	t_list	*tmp;

	tmp = *begin;
	
}
